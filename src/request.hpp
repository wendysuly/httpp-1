/*************************
 *         htt++         *
 *************************
 *     Request Module    *
 *      Header File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/
#include "jhash/JHash.hpp"
#include "jnet/JNet.hpp"
#include <jvect/JVect.hpp>
#include "exception.hpp"

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

//Bit hacky but it lets us default to std::string.
//Macros here are primarily to help readability:
//GET_VAR(varname, int) is a bit easier to understand than int varname = request.getVar<int>("varname"), and prevents having to type the variable name twice.

#define HTTPP_GET_STRING_VAR(name) std::string name = request.getRequestVars(#name)[0]
#define HTTPP_GET_OTHER_VAR(name, type) type name = request.getRequestVars<type>(#name)[0]
#define HTTPP_GET_THIRD_ARG(arg1, arg2, arg3, ...) arg3
#define HTTPP_CHOOSE_VAR_GETTER(...) HTTPP_GET_THIRD_ARG(__VA_ARGS__, HTTPP_GET_OTHER_VAR, HTTPP_GET_STRING_VAR)

#define HTTPP_GET_STRING_VARS(name) std::vector<std::string> name = request.getRequestVars(#name)
#define HTTPP_GET_OTHER_VARS(name, type) std::vector<type> name = request.getRequestVars<type>(#name)
#define HTTPP_CHOOSE_VARS_GETTER(...) HTTPP_GET_THIRD_ARG(__VA_ARGS__, HTTPP_GET_OTHER_VARS, HTTPP_GET_STRING_VARS)

#define GET_VARS(...)  HTTPP_CHOOSE_VARS_GETTER(__VA_ARGS__)(__VA_ARGS__)
#define GET_VAR(...) HTTPP_CHOOSE_VAR_GETTER(__VA_ARGS__)(__VA_ARGS__)

#define ADD_VAR(var) addVar(var, #var)
#define VAR(type, name) getVar<type>(#name)

namespace httpp
{
	class Header
	{
	public:
		Header(std::string name, std::string content) : m_name(name), m_content(content) {}
		std::string getName(){ return m_name; }
		std::string getContent(){ return m_content; }
		void setContent(std::string &s){ m_content = s; }
	private:
		std::string m_name, m_content;
	};

	//Headers and cookies need the same accessors, so just typedef.
	typedef Header Cookie;

	struct Converter: std::ctype<char>
	{
		Converter(): std::ctype<char>(get_table()) {}

	    static std::ctype_base::mask const* get_table()
	    {
	        static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());
	        return &rc[0];
	    }
	};

	class Variable
	{
	public:
		Variable(std::string content) : m_content(content)
		{
			m_stream.imbue(std::locale(std::locale(), new Converter()));
		}
		template<typename T=std::string>
		T get()
		{

			m_stream.str(m_content);
			T out;
			m_stream >> out;
			return out;
		}
	private:
		std::string m_content;
		std::stringstream m_stream;
	};

	class VarMap
	{
	public:
		VarMap(std::string name, std::string content) : m_name(name)
		{
			m_vars = new std::vector<Variable *>();
			m_vars->push_back(new Variable(content));
		}
		~VarMap()
		{
			for(Variable *v : *m_vars)
			{
				delete v;
			}
		}
		std::vector<Variable *> *getVars(){ return m_vars; }
		std::string getName(){ return m_name; }
		void add(std::string name)
		{
			m_vars->push_back(new Variable(name));
		}
	private:
		std::vector<Variable *>*m_vars;
		std::string m_name;
	};

	class Request
	{
	public:
		Request() : m_headers(&Header::getName, &Header::getContent), m_request_vars(&VarMap::getName, &VarMap::getVars) {}
		~Request(){ std::vector<Header *> headers = m_headers.getAll(); for(int i=headers.size()-1;i>=0;i--){ delete headers[i]; } }
		void create(std::string str);
		std::string getHeader(std::string name){ return m_headers[name]; }
		std::string operator[](std::string name){ return m_headers[name]; }
		template<typename T=std::string>
		std::vector<T> getRequestVars(std::string name)
		{
			std::vector<T> outVect;
			std::vector<Variable *>*vars = m_request_vars[name];
			for(Variable *v : *vars)
			{
				outVect.push_back(v->get<T>());
			}
			if(outVect.size() == 0)
			{
				outVect.push_back(T());
			}
			return outVect;
		}
		std::string getMethod(){ return m_method; }
		std::string getLocation(){ return m_location; }
		std::string getPath() { return m_location.erase(0, 1); }
		std::string getVersion(){ return m_http_version; }
		std::vector<Cookie> getCookies(){ return m_cookies; }
		std::string getCookie(std::string name);
		template<typename T>
		T getVar(std::string name){ return m_vars.get<T>(name); }
		template<typename T>
		void addVar(T var, std::string name){ m_vars.m_jvect_push(var, name); }
	protected:
		friend void httpp::listen(int port);
		void addHeader(std::string str);
		void addRequestVars( std::string str );
		void setCookies(std::string cookies);
	private:
		JHash::string_map<Header> m_headers;
		std::vector<Cookie> m_cookies;
		std::string m_method;
		std::string m_location;
		std::string m_http_version;
		JHash::basic_map<VarMap, std::vector<Variable *>> m_request_vars;
		JVect::jmap m_vars;
	};
}

#endif /* REQUEST_HPP_ */
