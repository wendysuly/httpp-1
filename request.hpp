/*************************
 *         htt++         *
 *************************
 *     Request Module    *
 *      Header File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/
#include "JHash.hpp"
#include "JNet.hpp"
#include "exception.hpp"

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

namespace httpp
{
	class Header
	{
	public:
		Header(std::string name, std::string content) : m_name(name), m_content(content) {}
		std::string getName(){ return m_name; }
		std::string getContent(){ return m_content.c_str(); }
		void setContent(std::string &s){ m_content = s; }
	private:
		std::string m_name, m_content;
	};

	class Request
	{
	public:
		Request() : m_headers(&Header::getName, &Header::getContent) {}
		~Request(){ std::vector<Header *> headers = m_headers.getAll(); for(int i=headers.size()-1;i>=0;i--){ delete headers[i]; } }
		void create(std::string str);
		std::string getHeader(std::string name){ return m_headers[name]; }
		std::string operator[](std::string name){ return m_headers[name]; }
		std::string getMethod(){ return m_method; }
		std::string getLocation(){ return m_location; }
		std::string getPath() { return m_location.erase(0, 1); }
		std::string getVersion(){ return m_http_version; }
		std::vector<std::string> getCookies(){ return m_cookies; }
	protected:
		friend void httpp::listen(int port);
		void addHeader(std::string str);
	private:
		JHash::string_map<Header> m_headers;
		std::vector<std::string> m_cookies;
		std::string m_method;
		std::string m_location;
		std::string m_http_version;
	};
}

#endif /* REQUEST_HPP_ */
