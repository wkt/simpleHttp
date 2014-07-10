#ifndef COOKIES_HPP_
#define COOKIES_HPP_
ff
#include <string>
#include <map>


class Cookies
{
	public:
		void getCookies(std::string str);
		/*
			void getCookies()
				Parses cookies from header, this is called in rev().
			Params:
				std::string str – string for parsing.
		*/

		void addCookie(std::string name, std::string value);
		/*
			void addCookies()
				Add cookie to cookie list.
			Params:
				std::string name
				std::string value
						
		*/

		void forceCookie(std::string name, std::string value);
		/*
			void forceCookies()
				Forces cookie to specifig value, server can't change this.
			Params:
				std::string name
				std::string value
		*/

		bool isForced(std::string name);
		/*
			bool isForced()
				Check if cookie is forced.
			Params:
				std::string name
			Retuns:
				true if is forced.
		*/

		std::string returnCookies();
		/*
			std::string returnCookies()
				Return cookies in string what can be sent to server.
		*/
		
		int getCookieValue(std::string str, std::string &res);
		/*
			int getCookiesValue();
				Get value of cookie.
			Params:
				std::string str – Name of cookie.
				std::string res – Value of cookie.
			Return:
				1 – Cookie was found.
				0 – Cookie wasnt found.
		*/

		void toggleDebug(bool value);
		void clearCookies();


	private:
		std::map<std::string, std::string> cookies;
		std::map<std::string, std::string> fcookies;
		bool debug;

};

#endif
