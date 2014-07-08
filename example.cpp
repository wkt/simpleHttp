#include <iostream>
#include <string>

#include "./simpleHttp/http.hpp"

using namespace std;

int main()
{
	string res, head;

	string server = "naurunappula.com";
	string port = "80";

	simpleHttp Client;

	Client.openConnection(server, port);

	Client.GET("/", Client.returnCookies(), res, head, true);

	Client.getHeaderValue("Server", res);
	cout << "Server: " << res << endl;

	cout << Client.returnCookies() << endl;

}
