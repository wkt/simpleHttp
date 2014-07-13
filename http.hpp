#ifndef HTTP_HPP_
#define HTTP_HPP_

#include <string>

#include "cookies.hpp"
#include "headers.hpp"

class simpleHttp : public Cookies, public Headers
{
	public:



		int doSend(std::string str);
		/*
		asdad	test
			doSend();
				sends data to server using send()

			Params:
				std::string str – Data to send.
			Return values:
				1 – Data were sent succesfully.
				-1 - send() failed.
		*/

		int openConnection(std::string _host, std::string _port = "80");
		/*
			openConnection();
			Tries to open connection to server

			Return values:
				1 – Connection is made succesfully.
				-1 – socket() has failed.
				-2 – getaddrinfo() has failed.
				-3 – connect() has failed.

		*/
		int GET(std::string q, std::string cookies, std::string &res, std::string &head, bool wait = true);
		/*
			GET()
				Makes GET request
			Params:
				std::string q – Querystring what will be sent.
				std::string cookies – Cookies what will be sent.
				sd::string &res – Response from server will go here.
				std::string &head – Header from server will go here.
				bool wait – If this is false server's reponse wont be revived.
			Return values:
				1 – Data has been sent to server.
				0 – Something has failed.
				-1 – Data could not have been sent to server.

		*/

		int POST(std::string q, std::string data, std::string cookies, std::string &res, std::string &head, bool wait = true);
		/*
			POST()
				Makes GET request

			Params:
				std::string q – Path.
				std::string data - Post data what will be sent to server.
				std::string cookies – Cookies what will be sent.
				sd::string &res – Response from server will go here.
				std::string &head – Header from server will go here.
				bool wait – If this is false server's reponse wont be revived.

			Return values:
				1 – Data has been sent to server.
				0 – Something has failed.
				-1 – Data could not have been sent to server.
		*/

		int HEAD(std::string q, std::string cookies, std::string &head);
		/*
			HEAD()
				Request headers from server.
			Params:
				std::string q – Path.
				std::string cookies – Cookies to be sent.
				std::string &head – This will be filled with header.
			Return values:
				1 – Data has been sent to server.
				0 – Something has failed.
				-1 – Data could not have been sent to server.
		*/

		int rev(std::string &data, std::string &head);
		/*
			rev()
				Revives data from server.
			Params:
				std::string &data – Response after will be stored her.
				std::string &headers - Headers will be stored here.
			Return values:
				1 – Data were succesfully revived.
				-1 – select() failed.
				-2 – Server closed connection.
				-3 – recv() failed.

		*/

        bool toggleRev(bool = true);
        /*

            toggleRev()
                Chooses should we skip rev() or not.
                This can make code much faster but server may try send that data later on rev().
        */
		void toggleDebug(bool val);

	protected:
		int reCreateSocket();

	private:
		int s;
		std::string host;
		std::string port;

        bool revstatus;
		bool debug;
};

#endif
