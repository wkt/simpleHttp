#ifndef COOKIES_HPP_
#define COOKIES_HPP_

#include <string>
#include <vector>
#include <map>


class Cookies
{
	public:
		void getCookies(std::string str);
		void addCookie(std::string name, std::string value);
		void delCookie(std::string str);
		int sendCookies();

		std::string returnCookies();
		int getCookieValue(std::string str, std::string &res);
		void toggleDebug(bool value);

	private:
		std::map<std::string, std::string> cookies;
		bool debug;

};

#endif
