#include <iostream>
#include <string>
#include <stdio.h>

#include "./simpleHttp/http.hpp"

using namespace std;

int main()
{

	cout << "Start: " << time(0) << endl;

	string res, head;

	string server = "google.com";
	string port = "80";

	simpleHttp Client;

	Client.toggleDebug(false);

	Client.openConnection(server, port);


	Client.GET("/", Client.returnCookies(), res, head, true);

	cout << res << endl;

	cout << "End: " << time(0) << endl;

}
