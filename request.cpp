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
	void Request::create(std::string str)
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
			if(str[i] == ' ')
			{
				i++;
				break;
			}
			if(i < len-1 && str[i] == '.' && str[i+1] == '/')
			{
				m_http_version = "HTTP/1.0";
				throw HTTPException(400, "INVALID LOCATION");
			}
			m_location += str[i];
		}
		while(str[i] == ' ')
			i++;
		for( ;i<len;i++)
			m_http_version += str[i];
		if(m_method == "" || m_location == "" || m_http_version == "")
		{
			m_http_version = "HTTP/1.0";
			throw HTTPException(400, "BAD REQUEST");
		}
		//std::cout << "Received new request: " << str << std::endl;
	}

	void Request::addHeader(std::string str)
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
			throw HTTPException(400, "INVALID HEADER");
		if(strToLower(name) == "cookie")
			m_cookies.push_back(content);
		else
		{
			Header *h = new Header(name, content);
			m_headers.push(h);
		}
		//std::cout << "Found header: " << str << std::endl;
	}
}
