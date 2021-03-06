#pragma once

/*************************
 *         htt++         *
 *************************
 *     Page Module       *
 *     Header File       *
 *************************/

#include <functional>
#include "TagStructs.hpp"
#include <sprawl/format/format.hpp>
#include <sprawl/network/network.hpp>
#include "request.hpp"
#include "util.hpp"

/*
 * This macro creates a class for each page the developer wants to create. This macro is mostly syntactic sugar (as is a lot of this library), but it makes
 * a cleaner approach to page-based HTML development that doesn't require the developer to learn the internals of the system behind it in order to use it.
 */
#define DeclarePage(name)	namespace Pages \
							{ \
								class page_##name : public httpp::BasePage{ \
									void do_layout(httpp::Request &request); \
								public: \
									page_##name() {} \
									~page_##name() {} \
									BasePage *clone() { return new page_##name(); } \
								}; \
							} \
							extern Pages::page_##name name;

#define DefinePage(name)	Pages::page_##name name; \
							inline void Pages::page_##name::do_layout(httpp::Request &request)

#define Page(name)	namespace Pages \
							{ \
								class page_##name : public httpp::BasePage{ \
									void do_layout(httpp::Request &request); \
								public: \
									page_##name() {} \
									~page_##name() {} \
									BasePage *clone() { return new page_##name(); } \
								}; \
							} \
							Pages::page_##name name; \
							inline void Pages::page_##name::do_layout(httpp::Request &request)

#define noimport if(!m_is_import)

namespace httpp
{

	class BaseSection;
	class PageMap;

	enum class httpStatus { rOK = 200, rBAD_REQUEST = 400, rNOT_FOUND = 404 };

	class BasePage
	{
	public:
		BasePage() : m_status(httpStatus::rOK), m_last_line_ended(true), m_message("OK") { }
		virtual ~BasePage() {}
		virtual BasePage *clone() = 0;
		std::string operator()(Request *r, int tabpad = 0, bool is_import = false)
		{
			m_request=r;
			m_outstream.str("");
			m_tabpad = tabpad;
			m_is_import = is_import;
			generateHeaders();
			do_layout(*m_request);
			return m_outstream.str();
		}
		httpStatus getStatus(){return m_status;}
		std::string getMessage(){return m_message;}
		std::string getHeaders()
		{
			std::stringstream ret;
			ret.str("");
			ret << m_outstream.str().length();
			setHeader("Content-Length", ret.str());
			ret.str("");
			ret << m_request->getVersion() << " " << static_cast<int>(m_status) << " " << m_message << std::endl;
			int size = m_headers.size();
			for(int i=0; i<size; i++)
				ret << m_headers[i].getName() << ": " << m_headers[i].getContent() << std::endl;
			ret << std::endl;
			return ret.str();
		}
		int getIntStatus(){return static_cast<int>(m_status);}


		Header *getHeader(const std::string &sName)
		{
			std::string name = strToLower(sName);
			int size=m_headers.size();
			for(int i=0;i<size;i++)
			{
				if(m_headers[i].getName() == name)
					return &m_headers[i];
			}
			return nullptr;
		}
		void setHeader(const std::string &sName, const std::string &content)
		{
			Header *h;
			std::string name = strToLower(sName);
			if((h=getHeader(name)) != nullptr)
				h->setContent(content);
			else
				m_headers.push_back(Header(name, content));
		}
		void addCookie(const std::string &name, const std::string &content)
		{
			m_headers.push_back(Header("Set-Cookie", sprawl::format::format("{0}={1}", name, content)));
		}

		Request *getRequest(){ return m_request; }
		friend BasePage &GetPageRef(const std::string &location);
		void setStatus(httpStatus r)
		{
			switch(r)
			{
			case httpStatus::rOK:			m_message = "OK";			break;
			case httpStatus::rBAD_REQUEST:	m_message = "BAD REQUEST";	break;
			case httpStatus::rNOT_FOUND: 	m_message = "NOT FOUND";	break;
			default:						m_message = "???";			break;
			}
			m_status = r;
		}
		void setMessage(const std::string &str){ m_message = str; }
		void setTag(Tags::BaseTag *Tag){ m_currentTag = Tag; }
	protected:
		friend class BaseSection;

		std::string pad_tabs();
		bool end_tag();
		void tag(const std::string &tagname);
		void make_x_tag(const std::string &tagname);
		std::string make_inline_tag(const std::string &str, const std::string &tagname);
		std::string fix_tabs(const std::string &str);
		bool execsection(BaseSection *p, std::function<void(void)> l);

		httpStatus Import(BasePage &p);

		template<typename T>
		void Print_(std::stringstream &s, T arg)
		{
			s << arg;
		}

		template<typename T, typename... Params>
		void Print_(std::stringstream &s, T arg, Params... params)
		{
			s << arg << " ";
			Print_(s, params...);
		}

		template<typename T, typename... Params>
		void $(T arg)
		{
			std::stringstream s;
			s << pad_tabs()  << arg;
			m_outstream << fix_tabs(s.str()) << std::endl;
			m_last_line_ended = true;
		}

		template<typename T, typename... Params>
		void $(T arg, Params... params)
		{
			std::stringstream s;
			s << pad_tabs()  << arg << " ";
			Print_(s, params...);
			m_outstream << fix_tabs(s.str()) << std::endl;
			m_last_line_ended = true;
		}

		/*
		 * $S - No space between arguments.
		 * Otherwise identical to $.
		 */

		template<typename T>
		void Print_S(std::stringstream &s, T arg)
		{
			s << arg;
		}

		template<typename T, typename... Params>
		void Print_S(std::stringstream &s, T arg, Params... params)
		{
			s << arg;
			Print_S(s, params...);
		}

		template<typename T, typename... Params>
		void $S(T arg)
		{
			std::stringstream s;
			s << pad_tabs()  << arg;
			m_outstream << fix_tabs(s.str()) << std::endl;
			m_last_line_ended = true;
		}

		template<typename T, typename... Params>
		void $S(T arg, Params... params)
		{
			std::stringstream s;
			s << pad_tabs()  << arg;
			Print_S(s, params...);
			m_outstream << fix_tabs(s.str()) << std::endl;
			m_last_line_ended = true;
		}

		/*
		 * $N - Replaces the trailing endline with a space.
		 * Otherwise identical to $.
		 */

		template<typename T, typename... Params>
		void $N(T arg)
		{
			std::stringstream s;
			s << pad_tabs()  << arg;
			m_outstream << fix_tabs(s.str()) << " ";
			m_last_line_ended = false;
		}

		template<typename T, typename... Params>
		void $N(T arg, Params... params)
		{
			std::stringstream s;
			s << pad_tabs()  << arg << " ";
			Print_(s, params...);
			m_outstream << fix_tabs(s.str()) << " ";
			m_last_line_ended = false;
		}

		/*
		 * $NN - No endline AND no space at the end.
		 * Otherwise identical to $.
		 */

		template<typename T, typename... Params>
		void $NN(T arg)
		{
			std::stringstream s;
			s << pad_tabs()  << arg;
			m_outstream << fix_tabs(s.str());
			m_last_line_ended = false;
		}

		template<typename T, typename... Params>
		void $NN(T arg, Params... params)
		{
			std::stringstream s;
			s << pad_tabs()  << arg << " ";
			Print_(s, params...);
			m_outstream << fix_tabs(s.str());
			m_last_line_ended = false;
		}

		/*
		 * $SN - No space between arguments.
		 * Replaces the trailing endline with a space.
		 * Otherwise identical to $.
		 */

		template<typename T>
		void Print_NS(std::stringstream &s, T arg)
		{
			s << arg;
		}

		template<typename T, typename... Params>
		void Print_NS(std::stringstream &s, T arg, Params... params)
		{
			s << arg;
			Print_NS(s, params...);
		}

		template<typename T, typename... Params>
		void $SN(T arg)
		{
			std::stringstream s;
			s << pad_tabs() << arg;
			m_outstream << fix_tabs(s.str()) << " ";
			m_last_line_ended = false;
		}

		template<typename T, typename... Params>
		void $SN(T arg, Params... params)
		{
			std::stringstream s;
			s << pad_tabs() << arg;
			Print_NS(s, params...);
			m_outstream << fix_tabs(s.str()) << " ";
			m_last_line_ended = false;
		}

		/*
		 * $SNN - No space between arguments.
		 * No endline AND no space.
		 * Directly concatenates all arguments and adds no space between calls.
		 */

		template<typename T, typename... Params>
		void $SNN(T arg)
		{
			std::stringstream s;
			s << pad_tabs() << arg;
			m_outstream << fix_tabs(s.str());
			m_last_line_ended = false;
		}

		template<typename T, typename... Params>
		void $SNN(T arg, Params... params)
		{
			std::stringstream s;
			s << pad_tabs() << arg;
			Print_NS(s, params...);
			m_outstream << fix_tabs(s.str());
			m_last_line_ended = false;
		}

		template<typename... Params>
		void $f(Params... params)
		{
			$(sprawl::format::format(params...));
		}

		template<typename... Params>
		void $Nf(Params... params)
		{
			$N(sprawl::format::format(params...));
		}

		template<typename... Params>
		void $NNf(Params... params)
		{
			$NN(sprawl::format::format(params...));
		}
		std::function<void(void)> m_lambdaFunc;
		bool m_sectionTracker;
		BaseSection *m_section;

		Request *m_request;
		bool m_is_import;
	private:
		void generateHeaders()
		{
			int size = m_headers.size();
			for(int i=size-1;i>=0;i--)
			{
				//We have headers we want to send every time. To save on memory allocation/deallocation costs,
				//let's step through this backward until we find one we know we're setting, and then break out.
				//This works because any added headers get added to the back of the list.
				if(m_headers[i].getName() == "Content-Type")
					break;
				m_headers.pop_back();
			}
			setHeader("Server", "htt++ 0.1 alpha");
			if(m_request->getVersion() == "HTTP/1.1" || strToLower((*m_request)["Connection"]) == "keep-alive")
				setHeader("Connection", "keep-alive");
			else
				setHeader("Connection", "close");
			setHeader("Content-Type", "text/html");
		}
		virtual void do_layout(Request &request) = 0;
		httpStatus m_status;
		std::vector<std::string> m_tagStack;
		bool m_last_line_ended;
		Tags::BaseTag *m_currentTag;
		std::stringstream m_outstream;
		std::string m_message;
		//A vector here is going to be more performant than a map because our most common operations
		//(clearing unneeded headers in generateHeaders and printing headers in formatHeaders)
		//involve stepping through the list, which is slower with a map.
		//Search operations will not be considerably slower due to the small number of headers each page has.
		std::vector<Header> m_headers;
		int m_tabpad;
	};

	class PageMap
	{
	public:
		PageMap(const std::string &s, BasePage &p, const std::string &ct) : m_name(s), m_content_type(ct), m_page(p) {}
		std::string getName(){ return m_name; }
		BasePage &getPage(){ return m_page; }
		std::string getContentType(){ return m_content_type; }
		std::string operator()(Request *request){ return m_page(request); }
	private:
		std::string m_name, m_content_type;
		BasePage &m_page;
	};
}
