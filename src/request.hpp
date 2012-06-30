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

//Bit hacky but it lets us default to std::string.
//Macros here are primarily to help readability:
//GET_VAR(varname, int) is a bit easier to understand than int varname = request.getVar<int>("varname"), and prevents having to type the variable name twice.

#define GET_STRING_VAR(name) std::string name = request.getVar(#name);
#define GET_OTHER_VAR(name, type) type name = request.getVar<type>(#name);
#define GET_THIRD_ARG(arg1, arg2, arg3, ...) arg3
#define CHOOSE_VAR_GETTER(...) GET_THIRD_ARG(__VA_ARGS__, GET_OTHER_VAR, GET_STRING_VAR)

#define GET_VAR(...)  CHOOSE_VAR_GETTER(__VA_ARGS__)(__VA_ARGS__)

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
		VarMap(std::string name, std::string content) : m_var(new Variable(content)), m_name(name) { }
		~VarMap(){ delete m_var; }
		Variable *getVar(){ return m_var; }
		std::string getName(){ return m_name; }
	private:
		Variable *m_var;
		std::string m_name;
	};

	class Request
	{
	public:
		Request() : m_headers(&Header::getName, &Header::getContent), m_vars(&VarMap::getName, &VarMap::getVar) {}
		~Request(){ std::vector<Header *> headers = m_headers.getAll(); for(int i=headers.size()-1;i>=0;i--){ delete headers[i]; } }
		void create(std::string str);
		std::string getHeader(std::string name){ return m_headers[name]; }
		std::string operator[](std::string name){ return m_headers[name]; }
		template<typename T=std::string>
		T getVar(std::string name)
		{
			Variable *v = m_vars[name];
			if(v)
				return m_vars[name]->get<T>();
			else
				return T();
		}
		std::string getMethod(){ return m_method; }
		std::string getLocation(){ return m_location; }
		std::string getPath() { return m_location.erase(0, 1); }
		std::string getVersion(){ return m_http_version; }
		std::vector<std::string> getCookies(){ return m_cookies; }
		void addVars( std::string str );
	protected:
		friend void httpp::listen(int port);
		void addHeader(std::string str);
	private:
		JHash::string_map<Header> m_headers;
		std::vector<std::string> m_cookies;
		std::string m_method;
		std::string m_location;
		std::string m_http_version;
		JHash::basic_map<VarMap, Variable> m_vars;
	};
}

#endif /* REQUEST_HPP_ */
