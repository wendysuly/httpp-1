/*************************
 *         htt++         *
 *************************
 *     Section Module    *
 *      Header File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#ifndef SECTION_HPP_
#define SECTION_HPP_

/*
 * The methods used here are similar to those used by the tags (see tags.hpp), only a small amount more complicated.
 * Since sections are defined objects by the developer, we can just create a new instance of it using the arguments supplied
 * by the developer. However, we then have to set the page parenting it to the page it's defined in - sections can't be called from
 * outside of a page object.
 *
 * Finally, we use a for loop for proper scoping (like in tags.hpp), and then create a lambda function. The last clause of
 * the for loop is the execsection function, which passes the lambda function we created to the section, letting any unique code
 * we want to run be run from inside the section, at a point defined by the developer.
 */
#define sect(obj, ...)	m_section = new obj(__VA_ARGS__); \
						m_section->setPage(this); \
						for(m_sectionTracker=true;m_sectionTracker;m_sectionTracker=execsection(m_section, m_lambdaFunc)) \
							m_lambdaFunc = [&]()

#define SECT(obj, ...)	m_section = new obj(__VA_ARGS__); \
						m_section->setPage(this); \
						execsection(m_section, [&](){})

/*
 * Syntactic sugar to improve the seamlessness and feel of the code and make it more appropriate for a page-oriented structure.
 * As with our handling of pages, this lets developers make use of the library without having to have much knowledge of its
 * internal methods of operation.
 *
 * The primary reason for these is simple coherence with the rest of the library.
 */
#define Section(name) class name : public httpp::BaseSection
#define SectionVars private
#define SectionInfo public
#define SectionLayout() void do_layout(std::function<void(void)> content)

namespace httpp
{
	class BaseSection
	{
	public:
		virtual ~BaseSection(){}
		virtual void do_layout(std::function<void(void)> name) = 0;
		void setPage(BasePage *page){ m_page = page; request = m_page->getRequest(); }
		void setTag(Tags::BaseTag *Tag){ m_page->setTag(Tag); }
	protected:
		void setStatus(httpStatus r){ m_page->setStatus(r); }

		std::string pad_tabs(){ return m_page->pad_tabs(); }
		bool end_tag(){ return m_page->end_tag(); }
		void tag(const std::string &tagname){ m_page->tag(tagname); }
		void make_x_tag(const std::string &tagname){ m_page->make_x_tag(tagname); }
		std::string make_inline_tag(const std::string &str, const std::string &tagname){ return m_page->make_inline_tag(str, tagname); }
		std::string fix_tabs(const std::string &str){ return m_page->fix_tabs(str); }

		template<typename... Params>
		void $(Params... params){ m_page->$(params...); }

		template<typename T, typename... Params>
		void $S(T arg, Params... params){ m_page->$S(params...); }

		template<typename T, typename... Params>
		void $N(T arg, Params... params){ m_page->$N(params...); }

		template<typename T, typename... Params>
		void $NN(T arg, Params... params){ m_page->$NN(params...); }

		template<typename T, typename... Params>
		void $SN(T arg, Params... params){ m_page->$SN(params...); }

		template<typename T, typename... Params>
		void $SNN(T arg, Params... params){ m_page->$SNN(params...); }

		template<typename... Params>
		void $f(Params... params){ m_page->$f(params...); }

		template<typename... Params>
		void $Nf(Params... params){ m_page->$Nf(params...); }

		template<typename... Params>
		void $NNf(Params... params){ m_page->$NNf(params...); }

		BasePage *m_page;
		Request *request;
	};
}

#endif /* SECTION_HPP_ */
