#include <iostream>
#include <string>
#include <stdio.h>

#include "./simpleHttp/http.hpp"

using namespace std;

int main()
{
	string res, head;

	string server = "imgur.com";
	string port = "80";

	simpleHttp Client;

	Client.toggleDebug(true);

	if (Client.openConnection(server, port) != 1)
	{
		perror("Can't open connection: ");
		return 1;
	}

	Client.GET("/", Client.returnCookies(), res, head, true);

	Client.getHeaderValue("Server", res);
	cout << "Server: " << res << endl;

	cout << Client.returnCookies() << endl;

}
