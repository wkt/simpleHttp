#ifndef HEADERS_HPP_
#define HEADERS_HPP_

#include <string>
#include <map>

class Headers
{
	public:
		void parseHeaders(std::string head);
		int getStatus();
		std::string getStatusMessage();
		std::string getHeader();

		void addHeaderValue(std::string name, std::string value);
		int getHeaderValue(std::string str, std::string &res);

		virtual void toggleDebug(bool val);

	protected:
		std::string header;	

	private:

		std::map<std::string, std::string> headerValues;
		int status;
		std::string statusMessage;
		bool debug;
		std::map<std::string, std::string> headers;
};

#endif
