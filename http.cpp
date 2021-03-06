#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <vector>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <string>
#include <vector>

#include "http.hpp"

using namespace std;

int simpleHttp::rev(string &data, string &headers)
{
	if (debug)
		cout << "[ rev() ]" << endl;

	data.clear();

	int n, rv, r;
	fd_set readfds;
	struct timeval tv;

	FD_ZERO(&readfds);
	FD_SET(s, &readfds);

	n = s + 1;

	tv.tv_sec = 1;
	tv.tv_usec = 0;

	bool haveHeader = false;

	for (size_t i = 0; rv = select(n, &readfds, NULL, NULL, &tv); i++)
	{

		if (rv <= 0)
			break;

		char buf[5000];
		r = recv(s, buf, sizeof buf, 0);

		if (r <= 0)
			break;

		string str = string(buf);


		if (( str.find("\r\n\r\n") != string::npos) && (haveHeader == false ))
		{
			size_t headerEnd = str.find("\r\n\r\n") + 3;

			headers = str.substr(0, headerEnd);

			parseHeaders(headers);
			getCookies(headers);
			data += str.substr(headerEnd, str.size() - headerEnd);

			haveHeader = true;
		}
		else
		{
			data += str;
		}
	}

	string res;
	getHeaderValue("Connection", res);
	if ((res == "close") || (res.empty()))
		reCreateSocket();

	if (r <= 0)
		return r - 2;
	if (rv < 0)
		return rv;
	return 1;
}

int simpleHttp::doSend(string tmp)
{
	string str = tmp;
	int sent;

	while(1)
	{
		sent = send(s, tmp.c_str(), tmp.size(), 0);
		if (sent < 0)
			return sent;
		if (sent != str.size())
		{
			str = str.substr(sent , str.size() - sent  );
			continue;
		}
		break;
	}
	return 1;
}


int simpleHttp::GET(string q, string cookies, string &res, string &head, bool wait)
{
	if (debug)
		cout << "[ GET(" + q + ") ]" << endl;
	string str = "GET " + q + " HTTP/1.1\r\nHost: " + host + "\r\n" + cookies + "Connection: keep-alive\r\n\r\n";
	if (doSend(str) == 1)
		if (wait)
			return rev(res, head);
	return 0;
}

int simpleHttp::POST(std::string q, std::string data, string cookies, string &res, string &head, bool wait)
{
	if (debug)
		cout << "[ POST(" << q << ", " << data << + ") ]"  << endl;

	string str = "POST " + q + " HTTP/1.1\r\nHost: " + host + "\r\n" + cookies + "Content-Type: application/x-www-form-urlencoded\r\nContent-Length:" + to_string(data.size()) + "\r\nConnection: keep-alive\r\n\r\n" + data;
	if (doSend(str) == 1)
		if (wait)
			return rev(res, head);
	return 0;
}


int simpleHttp::HEAD(string q, string cookies, string &head)
{
	string tmp;
	if (debug)
		cout << "[ HEAD(" << q << ") ]" << endl;
	string str = "HEAD " + q + " HTTP/1.1\r\nHost: " + host + "\r\n" + cookies + "Connection: keep-alive\r\n\r\n";
	if (doSend(str) == 1)
		return rev(tmp, head);
	return 0;
}


int simpleHttp::openConnection(string _host, string _port)
{

	if ((!host.empty()) && (host != _host))
		clearCookies();

	struct addrinfo hints;
	struct addrinfo *servinfo;

	host = _host;
	port = _port;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host.c_str(), port.c_str(), &hints, &servinfo) != 0) { return -2; }

	s = socket (servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	if (s == -1) { return -1; }

	if (connect(s, servinfo->ai_addr, servinfo->ai_addrlen) != 0) { return -3; }
	freeaddrinfo(servinfo);

	return 1;
}

int simpleHttp::reCreateSocket()
{
	close(s);
	return openConnection(host, port);
}


void simpleHttp::toggleDebug(bool val)
{
	Headers::toggleDebug(val);
	Cookies::toggleDebug(val);
	debug = val;
}
