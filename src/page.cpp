/*************************
 *         htt++         *
 *************************
 *     Page Module       *
 *     Source File       *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#include "page.hpp"
#include "section.hpp"
#include "util.hpp"

namespace httpp
{
	bool BasePage::execsection(BaseSection *p, std::function<void(void)> l)
	{
		p->do_layout(l);
		delete p;
		return false;
	}

	std::string BasePage::pad_tabs()
	{
		std::string s = "";
		if(m_last_line_ended == false)
			return "";
		for(int i=0; i<m_tabpad; i++)
			s+="\t";
		for(unsigned int i=0; i<m_tagStack.size(); i++)
			s+="\t";
		return s;
	}

	bool BasePage::end_tag()
	{
		std::string tagname = m_tagStack[m_tagStack.size()-1];
		m_tagStack.pop_back();
		m_outstream << pad_tabs() << JFormat::format("</{0}>", tagname) << std::endl;
		return false;
	}

	void BasePage::tag(const std::string &tagname)
	{
		m_outstream << pad_tabs() << JFormat::format("<{0}{1}>", tagname, m_currentTag->get_args()) << std::endl;
		delete m_currentTag;
		m_tagStack.push_back(tagname);
	}

	std::string BasePage::make_inline_tag(const std::string &str, const std::string &tagname)
	{
		std::string args = m_currentTag->get_args();
		delete m_currentTag;
		return JFormat::format("<{0}{1}>{2}</{0}>", tagname, args, str);
	}

	void BasePage::make_x_tag(const std::string &tagname)
	{
		m_outstream << pad_tabs() << JFormat::format("<{0}{1} />", tagname, m_currentTag->get_args()) << std::endl;
		delete m_currentTag;
	}

	std::string BasePage::fix_tabs(const std::string &str)
	{
		int len = str.length();
		std::string out;
		for(int i=0;i<len;i++)
		{
			if(str[i] == '\n' || str[i] == '\r')
			{
				out += str[i];
				out += pad_tabs();
			}
			else
			{
				out += str[i];
			}
		}
		return out;
	}

	httpStatus BasePage::Import(BasePage &p)
	{
		m_outstream << p(m_request, m_tagStack.size(), true);
		return p.getStatus();
	}
}
