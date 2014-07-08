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
	char tmp[1000];
	int i = 0;
	string tmp2;

	while(recv(s, tmp, sizeof tmp, 0) > 0)
	{
		if (i == 0)
		{
			parseHeaders(tmp);
			getCookies(tmp);	
			if (debug)
				cout << "[ " <<  getStatus() << " ]" << endl;
		} else {
			data += tmp;
		}
		i++;
	}
	string res;
	close(s);
	return 1;
}

int simpleHttp::GET(string q, string cookies, string &res, string &head, bool wait)
{
	string tmp;
	getHeaderValue("connection", tmp);
	if (res == "close" || (res == ""))
		reCreateSocket();
	if (debug)
		cout << "[ GET(" + q + ") ]" << endl;
	string str = "GET " + q + " HTTP/1.1\r\nHost: " + host + "\r\nAccept: text/html\r\n" + cookies + "Refer: http://" + host + "/\r\nConnection: keep-alive\r\n\r\n";
	if (send(s, str.c_str(), str.size(), 0) > 0)
	{
		if (wait)
			rev(res, head);
		return 1;
	}
	return 0;
}

int simpleHttp::POST(std::string q, std::string data, string cookies, string &res, string &head, bool wait)
{
	string tmp;
	getHeaderValue("connection", tmp);
	if (res == "close" || (res == ""))
		reCreateSocket();
	if (debug)
		cout << "[ POST(" << q << ", " << data << + ") ]"  << endl;

	string str = "POST " + q + " HTTP/1.1\r\nHost: " + host + "\r\nAccept: text/html\r\n" + cookies + "Refer: http://" + host + "/\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length:" + to_string(data.size()) + "\r\nConnection: keep-alive\r\n\r\n" + data;
	if (send(s, str.c_str(), str.size(), 0) > 0)
	{
		if (wait)
			rev(res, head);
		return 1;
	}
	return 0;
}

int simpleHttp::openConnection(string _host, string _port)
{
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
	openConnection(host, port);
}

int simpleHttp::sendCookies()
{
	string res, head;
	GET("/", returnCookies(), res, head, false);
	if (res.find("OK") == 0) return 1;
	return -1;
}

void simpleHttp::toggleDebug(bool val)
{
	Headers::toggleDebug(val);
	Cookies::toggleDebug(val);
	debug = val;
}