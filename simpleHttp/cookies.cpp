#include "cookies.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
	HTTP/1.1 302 Found
	Date: Sun, 06 Jul 2014 20:28:34 GMT
	Server: Apache
	Expires: Thu, 19 Nov 1981 08:52:00 GMT
	Last-Modified: Sun, 06 Jul 2014 20:28:34 GMT
	Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0
	Pragma: no-cache
	Set-Cookie: mid=x; expires=Wed, 30-Dec-2015 22:00:00 GMT; path=/; domain=.naurunappula.com
	Set-Cookie: PHPSESSID=x; path=/; domain=.naurunappula.com
	Set-Cookie: lid=1; expires=Wed, 30-Dec-2015 22:00:00 GMT; path=/; domain=.naurunappula.com
	Set-Cookie: L=x; path=/; domain=.naurunappula.com
	Set-Cookie: ch=x; expires=Wed, 06-Aug-2014 20:28:34 GMT; path=/; domain=.naurunappula.com
	Set-Cookie: ui=x; expires=Wed, 06-Aug-2014 20:28:34 GMT; path=/; domain=.naurunappula.com
	Set-Cookie: lid=x; expires=Wed, 30-Dec-2015 22:00:00 GMT; path=/; domain=.naurunappula.com
	Set-Cookie: fid=x; path=/; domain=.naurunappula.com
	Location: /
	Content-Length: 0
	Connection: close
	Content-Type: text/html; charset=utf-8
*/

void Cookies::getCookies(string str)
{
	if (debug)
		cout << "[ getCookies() ]" << endl;

	size_t nameStart = 0;
	while(str.find("Set-Cookie: ", nameStart + 1) != string::npos)
	{
		nameStart = str.find("Set-Cookie: ", nameStart) + 12;
		size_t nameEnd = str.find("=", nameStart);
		size_t valueEnd = str.find("; ", nameStart) - 2;

		size_t domainStart = str.find("domain=", nameStart) + 6;
		size_t domainEnd = str.find("\r\n", nameStart);

		string cookieName = str.substr(nameStart, nameEnd - nameStart );
		string cookieValue = str.substr(nameEnd + 1, valueEnd - nameEnd + 1);

		string domain = str.substr(domainStart, domainEnd - domainStart);

		addCookie(cookieName, cookieValue);
	}
	return;
}

void Cookies::addCookie(string name, string value)
{
	cookies[name] = value;
}

int Cookies::getCookieValue(string str, string &res)
{
	if ( cookies.find(str) != cookies.end() )
	{
		res = cookies[str];
		return 1;
	}
	return 0;
}

string Cookies::returnCookies()
{
	string res = "Cookie: ";
	for (map<string, string>::iterator p = cookies.begin(); p != cookies.end(); ++p)
		res += p->first + "=" + p->second + "; ";
	if (res != "Cookie: ")
	{
		res.pop_back();
		res.pop_back();
		res += "\r\n";
	} else {
		res = "";
	}
	return res;
}

void Cookies::toggleDebug(bool val)
{
	debug = val;
}

void Cookies::clearCookies() { cookies.clear(); }
