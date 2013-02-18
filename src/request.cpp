/*************************
 *         htt++         *
 *************************
 *     Request Module    *
 *      Source File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#include "request.hpp"
#include "util.hpp"

namespace httpp
{
	void Request::create(const std::string &str)
	{
		int len = str.length();
		int i = 0;
		for( ;i<len;i++)
		{
			if(str[i] == ' ')
			{
				i++;
				break;
			}
			m_method += str[i];
		}
		while(str[i] == ' ')
			i++;
		for( ;i<len;i++)
		{
			if(str[i] == ' ' || str[i] == '?')
			{
				i++;
				break;
			}
			if(i < len-1 && str[i] == '.' && (str[i+1] == '/' || (str[i+1] == '.' && str[i+2] == '/')))
			{
				m_http_version = "HTTP/1.0";
				throw HTTPException(400, "INVALID LOCATION");
			}
			m_location += str[i];
		}
		if(str[i-1] == '?')
		{
			std::string vars;
			for( ;i<len;i++)
			{
				if(str[i] == ' ')
				{
					i++;
					break;
				}
				vars += str[i];
			}
			addRequestVars(vars);
		}
		while(str[i] == ' ')
			i++;
		for( ;i<len;i++)
			m_http_version += str[i];
		if(m_method == "" || m_location == "" || m_http_version == "")
		{
			m_http_version = "HTTP/1.0";
			std::cout << "Bad HTTP string:" << str << " (" << m_method << ", " << m_location << ", " << m_http_version << ")" << std::endl;
			throw HTTPException(400, "BAD REQUEST");
		}
		//std::cout << "Received new request: " << str << std::endl;
	}

	void Request::addHeader(const std::string &str)
	{
		int len = str.length();
		int i = 0;
		std::string name;
		std::string content;
		for( ;i<len;i++)
		{
			if(str[i] == ':')
			{
				i++;
				break;
			}
			name += str[i];
		}
		while(str[i] == ' ')
			i++;
		for( ;i<len;i++)
			content += str[i];
		if(name == "" || content == "")
		{
			std::cout << "Bad header." << std::endl;
			throw HTTPException(400, "INVALID HEADER");
		}
		if(strToLower(name) == "cookie")
			setCookies(content);
		else
		{
			m_headers.push(Header(name, content));
		}
		//std::cout << "Found header: " << str << std::endl;
	}

	bool ishex(char c)
	{
		switch(c)
		{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				return true;
			default:
				return false;
		}
	}

	void Request::addRequestVars(const std::string &str)
	{
		std::string name;
		std::string content;
		int hexchr;
		std::string hexstr;
		std::stringstream s;
		bool in_name = true;
		int len=str.length();
		for(int i=0;i<len;i++)
		{
			if(str[i] == '=' || str[i] == '&')
			{
				in_name = !in_name;
				if(in_name)
				{
					if(m_request_vars.find(name) != m_request_vars.end())
					{
						std::vector<Variable> &v = m_request_vars[name].getVars();
						v.push_back(Variable(content));
					}
					else
					{
						m_request_vars.push(VarMap(name, content));
					}
					name = "";
					content = "";
				}
				continue;
			}
			if(str[i] == '%' && ishex(str[++i]))
			{
				do
				{
					hexstr += str[i];
					i++;
				}while(ishex(str[i]));
				s << std::hex << hexstr;
				s >> hexchr;
				if(in_name)
					name += static_cast<char>(hexchr);
				else
					content += static_cast<char>(hexchr);
				i--;
				continue;
			}
			if(in_name)
				name += str[i];
			else
				content += str[i];
		}

		if(m_request_vars.find(name) != m_request_vars.end())
		{
			std::vector<Variable> &v = m_request_vars[name].getVars();
			v.push_back(Variable(content));
		}
		else
		{
			m_request_vars.push(VarMap(name, content));
		}
	}

	void Request::setCookies(const std::string &str)
	{
		std::string name;
		std::string content;
		int hexchr;
		std::string hexstr;
		std::stringstream s;
		bool in_name = true;
		int len=str.length();
		for(int i=0;i<len;i++)
		{
			if(str[i] == '=' || str[i] == ';')
			{
				in_name = !in_name;
				if(in_name)
				{
					m_cookies.push_back(Cookie(name, content));
					name = "";
					content = "";
				}
				if(str[i] == ';')
				{
					//move forward 'till we've got a non-space character.
					while(str[++i] == ' '){}
				}
				continue;
			}
			if(str[i] == '%' && ishex(str[++i]))
			{
				do
				{
					hexstr += str[i];
					i++;
				}while(ishex(str[i]));
				s << std::hex << hexstr;
				s >> hexchr;
				if(in_name)
					name += static_cast<char>(hexchr);
				else
					content += static_cast<char>(hexchr);
				i--;
				continue;
			}
			if(in_name)
				name += str[i];
			else
				content += str[i];
		}
		m_cookies.push_back(Cookie(name, content));
	}

	std::string Request::getCookie(const std::string &name)
	{
		for(unsigned int i = 0; i < m_cookies.size(); i++)
		{
			if(m_cookies[i].getName() == name)
			{
				return m_cookies[i].getContent();
			}
		}
		return "";
	}
}
