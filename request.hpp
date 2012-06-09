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
