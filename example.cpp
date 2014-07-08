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
		cout << "Can't open connection" << endl;
		perror("");
		return 1;
	}

	Client.GET("/", Client.returnCookies(), res, head, true);

	cout << res << endl;


	if (Client.getHeaderValue("Server", res) == 1)
		cout << "Server: " << res << endl;

	cout << Client.returnCookies() << endl;

}
