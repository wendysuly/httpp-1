/*************************
 *         htt++         *
 *************************
 *   Exceptions Module   *
 *     Header File       *
 *************************
 * www.git-hub.com/httpp *
 *************************/
#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <sstream>
#include <string>

namespace httpp
{
	class GenericException : public std::exception
	{
	public:
		GenericException(std::string str) throw(){ m_what = str; }
		const char *what() const throw(){ return m_what.c_str(); }
		~GenericException() throw() {}
	private:
		std::string m_what;
	};

	class HTTPException : public std::exception
	{
	public:
		HTTPException(int i, std::string str) throw(){ m_code = i; m_msg = str; }
		const char *what() const throw(){ std::stringstream s; s << m_code << " " << m_msg; return s.str().c_str(); }
		const char *getMsg() const throw() { return m_msg.c_str(); }
		int getCode() const throw() { return m_code; }
		~HTTPException() throw() {}
	private:
		std::string m_msg;
		int m_code;
	};
}

#endif /* EXCEPTION_HPP_ */
