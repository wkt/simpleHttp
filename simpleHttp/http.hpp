#ifndef HTTP_HPP_
#define HTTP_HPP_

#include <string>

#include "cookies.hpp"
#include "headers.hpp"

class simpleHttp : public Cookies, public Headers
{
	public:
		int openConnection(std::string _host, std::string _port);
		int doSend(std::string str, std::string &res);

		int GET(std::string q, std::string cookies, std::string &res, std::string &head, bool wait);
		int POST(std::string q, std::string data, std::string cookies, std::string &res, std::string &head, bool wait);

		int rev(std::string &data, std::string &head);

		int sendCookies();
		int askForCookies(std::string res);

		void toggleDebug(bool val);

	protected:
		int reCreateSocket();

	private:
		int s;
		std::string host;
		std::string port;

		bool debug;
};

#endif
