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
	//void listen(int port);
	class httpp_server;

	class Header
	{
	public:
		Header(const std::string &name, const std::string &content) : m_name(name), m_content(content) {}
		std::string getName(){ return m_name; }
		std::string getContent(){ return m_content; }
		void setContent(const std::string &s){ m_content = s; }
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
		Variable(const std::string &content) : m_content(content)
		{
			m_stream.imbue(std::locale(std::locale(), new Converter()));
		}
		Variable(const Variable &v)
		{
			m_stream.imbue(std::locale(std::locale(), new Converter()));
			m_content = v.m_content;
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
		VarMap(const std::string &name, const std::string &content) : m_vars(std::vector<Variable>()), m_name(name)
		{
			m_vars.push_back(Variable(content));
		}
		std::vector<Variable> &getVars(){ return m_vars; }
		std::string getName(){ return m_name; }
		void add(const std::string &name)
		{
			m_vars.push_back(Variable(name));
		}
	private:
		std::vector<Variable> m_vars;
		std::string m_name;
	};

	class Request
	{
	public:
		Request() : m_headers(&Header::getName, &Header::getContent), m_request_vars(&VarMap::getName, &VarMap::getVars) {}
		~Request(){ }
		void create(const std::string &str);
		std::string getHeader(const std::string &name){ return m_headers[name].getContent(); }
		std::string operator[](const std::string &name){ return m_headers[name].getContent(); }
		template<typename T=std::string>
		std::vector<T> getRequestVars(const std::string &name)
		{
			std::vector<T> outVect;
			if(m_request_vars.find(name) == m_request_vars.end())
			{
				outVect.push_back(T());
				return outVect;
			}
			std::vector<Variable> &vars = m_request_vars[name].getVars();
			for(Variable &v : vars)
			{
				outVect.push_back(v.get<T>());
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
		std::string getCookie(const std::string &name);
		template<typename T>
		T getVar(const std::string &name){ return m_vars.get<T>(name); }
		template<typename T>
		void addVar(T var, const std::string &name){ m_vars.m_jvect_push(var, name); }
	protected:
		friend class httpp_server;
		//friend void listen(int port);
		void addHeader(const std::string &str);
		void addRequestVars( const std::string &str );
		void setCookies(const std::string &cookies);
	private:
		JHash::map<Header> m_headers;
		std::vector<Cookie> m_cookies;
		std::string m_method;
		std::string m_location;
		std::string m_http_version;
		JHash::map<VarMap> m_request_vars;
		JVect::jmap m_vars;
	};
}

#endif /* REQUEST_HPP_ */
