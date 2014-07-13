#include <iostream>
#include <string>
#include <vector>

#include "headers.hpp"

using namespace std;

/*
	HTTP/1.1 200 OK
	Date: Sat, 05 Jul 2014 22:58:17 GMT
	Server: Apache
	Expires: Mon, 26 Jul 1997 05:00:00 GMT
	Last-Modified: Sat, 05 Jul 2014 22:58:17 GMT
	Cache-Control: no-store, no-cache, must-revalidate
	Cache-Control: post-check=0, pre-check=0
	Pragma: no-cache
	Set-Cookie: mid=xxx; expires=Wed, 30-Dec-2015 22:00:00 GMT; path=/; domain=.naurunappula.com
	Set-Cookie: lid=1; expires=Wed, 30-Dec-2015 22:00:00 GMT; path=/; domain=.naurunappula.com
	Set-Cookie: v_xxx=1; expires=Sat, 05-Jul-2014 23:03:17 GMT; path=/; domain=.naurunappula.com
	Set-Cookie: PI=1; path=/; domain=.naurunappula.com
	Connection: close
	Transfer-Encoding: chunked
	Content-Type: text/html; charset=utf-8
*/

void Headers::parseHeaders(string str)
{
	if (debug)
		cout << "[ parseHeaders() ]" << endl;
	if (!str.empty())
	{

		size_t statusStart = str.find(" ") + 1;
		status = atoi( str.substr(statusStart, str.find(" ", statusStart) - statusStart).c_str() );

		size_t msgStart = str.find(" ", statusStart) + 1;
		statusMessage = str.substr(msgStart, str.find("\r\n") - msgStart);

		size_t lineStart = 0;

		while(str.find("\r\n", lineStart + 1) != string::npos)
		{
			lineStart = str.find("\r\n", lineStart) + 2;
			size_t nameEnd = str.find(": ", lineStart);

			size_t valueStart = nameEnd + 2;
			size_t valueEnd = str.find("\r\n", valueStart);

			if (str.find("Set-Cookie", lineStart) == lineStart)
				continue;
			if (lineStart > valueStart)
				continue;
			if (str.find(" ", lineStart) < (str.find(": ", lineStart)))
				continue;

			string settingName = str.substr(lineStart, nameEnd - lineStart);
			string settingValue = str.substr(valueStart, valueEnd - valueStart);

			//cout << settingName << endl;
			//cout << settingValue << endl;

			addHeaderValue(settingName, settingValue);
		}
		if (debug)
			cout << "[ " << getStatus() << " ]" << endl;

		return;
	}

	status = 0;
	statusMessage.erase();

	return;
}

void Headers::addHeaderValue(string name, string value)
{
	headers[name] = value;
}

int Headers::getHeaderValue(string str, string &res)
{
	if (headers.find(str) != headers.end())
	{
		res = headers[str];
		return 1;
	}
	return 0;
}


int Headers::getStatus() { return status; }
string Headers::getStatusMessage() { return statusMessage; }
string Headers::getHeader() { return header; }

void Headers::toggleDebug(bool val)
{
	debug = val;
}
