/*************************
 *         htt++         *
 *************************
 * Tag Structures Module *
 *      Header File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#ifndef TAGSTRUCTS_HPP_
#define TAGSTRUCTS_HPP_

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

/*
 * Macros used to create tags. These are only used locally and are used to quickly and easily define large numbers of similar classes that all derive from BaseTag.
 * Each one defines a get_args() function that returns any parameters that have been set, and a constructor that calls populate_args() on the variadic arguments passed to the macro.
 */

#define DECLARE_TAG2(tag, ...)	class tag : public BaseTag \
								{ \
								private: \
									static std::vector<std::string> m_arg_names; \
								protected: \
									TagParam __VA_ARGS__; \
									std::string get_args() \
									{ \
										return argify( m_arg_names, format_args(0, m_num_args, __VA_ARGS__) ); \
									} \
									tag(){ populate_args( m_arg_names, #__VA_ARGS__ ); } \
									virtual ~tag(){ } \
								}

/*
 * This macro is used to populate the HTML5 standard attributes shared by all tags.
 */
#define DECLARE_TAG(...)	DECLARE_TAG2(__VA_ARGS__, accesskey, Class, contenteditable, contextmenu, dir, draggable, hidden, id, lang, spellcheck, Style, tabindex, Title, \
							onabort, onblur, oncanplay, oncanplaythrough, onchange, onclick, oncontextmenu, ondblclick, ondrag, ondragend, \
							ondragenter, ondragleave, ondragover, ondragstart, ondrop, ondurationchange, onemptied, onended, onerror, onfocus, \
							onformchange, onforminput, onimput, oninvalid, onkeydown, onkeypress, onkeyup, onload, onloadeddata, \
							onloadedmetadata, onloadstart, onmousedown, onmousemove, onmouseout, onmouseover, onmouseup, onmousewheel, \
							onpause, onplay, onplaying, onprogress, onratechange, onreadystatechange, onscroll, onseeked, onseeking, \
							onselect, onshow, onstalled, onsubmit, onsuspend, ontimeupdate, onvolumechange, onwaiting)

namespace httpp
{
	namespace Tags
	{
		//Simple base tag class that all tags derive from.
		class BaseTag
		{
		protected:
			int m_num_args;
		public:
			virtual std::string get_args() = 0;
			BaseTag() : m_num_args(0) {}
			virtual ~BaseTag(){ }
		};

		//Since attributes in HTML can be string, int, or bool, we have a class that accepts all three and converts them into a string.
		class TagParam
		{
		public:
			TagParam() : m_str(""){}
			TagParam &operator =(const int &i){std::stringstream s; s<<i; m_str=s.str(); return *this;}
			TagParam &operator =(const std::string &s){m_str = s; return *this;}
			TagParam &operator =(const char *s){m_str = s; return *this;}
			TagParam &operator =(char c){m_str = c; return *this;}
			TagParam &operator =(const bool &b){m_str = (b ? "_B__TRUE" : "_B__FALSE"); return *this;}
			bool operator !=(const std::string &s){return m_str != s;}
			bool operator ==(const std::string &s){return m_str == s;}
			TagParam operator +(const std::string &s){m_str += s; return *this;}
			std::string str(){return m_str;}
		private:
			std::string m_str;
		};

		template<typename ...Params>
		const char * format_args(int i, int max, TagParam &p, Params&... params)
		{
			if(max==0)
				return "";
			static std::stringstream s;
			s.str("");
			if(p == "")
				s << format_args(i+1, max, params...);
			else
				s << i << "\v" << p.str() << "\a" << format_args(i+1, max-1, params...);
			return s.str().c_str();
		}
		const char *format_args(int i, int max, TagParam &p);
		void populate_args(std::vector<std::string> &v, std::string s);
		std::string argify(std::vector<std::string> &v, const char *s);

		/*
		 * Declaring tags:
		 *
		 * All tags are html 5 compatible, so they can accept any of the standard properties or events supported by html 5.
		 * To declare a tag, the syntax is:
		 * DECLARE_TAG(<tagname>, <attributes>...)
		 * Where attributes are properties specific to that tag.
		 */
		DECLARE_TAG(a, href, target, ping, rel, media, hreflang, type);
		DECLARE_TAG(abbr);
		DECLARE_TAG(address);
		DECLARE_TAG(area, alt, coords, shape, href, target, ping, rel, media, hreflang, type);
		DECLARE_TAG(article);
		DECLARE_TAG(aside);
		DECLARE_TAG(audio, src, preload, autoplay, loop, controls);
		DECLARE_TAG(b);
		DECLARE_TAG(base, href, target);
		DECLARE_TAG(bb, type);
		DECLARE_TAG(bdo);
		DECLARE_TAG(blockquote, cite);
		DECLARE_TAG(body);
		DECLARE_TAG(br);
		DECLARE_TAG(button, autofocus, disabled, form, formaction, formenctype, formmethod, formnovalidate, formtarget, name, type, value);
		DECLARE_TAG(canvas, width, height);
		DECLARE_TAG(caption);
		DECLARE_TAG(cite);
		DECLARE_TAG(code);
		DECLARE_TAG(col, span);
		DECLARE_TAG(colgroup, span);
		DECLARE_TAG(command, type, label, icon, disabled, checked, radiogroup, Default);
		DECLARE_TAG(datagrid, disabled, multiple);
		DECLARE_TAG(datalist, data);
		DECLARE_TAG(dd);
		DECLARE_TAG(del, cite, datetime);
		DECLARE_TAG(details, open);
		DECLARE_TAG(dfn);
		DECLARE_TAG(div);
		DECLARE_TAG(dl);
		DECLARE_TAG(dt);
		DECLARE_TAG(em);
		DECLARE_TAG(embed, src, type, width, height);
		DECLARE_TAG(eventsource, src);
		DECLARE_TAG(fieldset, disabled, form, name);
		DECLARE_TAG(figcaption);
		DECLARE_TAG(figure);
		DECLARE_TAG(footer);
		DECLARE_TAG(form, accept_charset, action, enctype, method, name, novalidate, target);
		DECLARE_TAG(h1);
		DECLARE_TAG(h2);
		DECLARE_TAG(h3);
		DECLARE_TAG(h4);
		DECLARE_TAG(h5);
		DECLARE_TAG(h6);
		DECLARE_TAG(head);
		DECLARE_TAG(header);
		DECLARE_TAG(hgroup);
		DECLARE_TAG(hr);
		DECLARE_TAG(html, manifest);
		DECLARE_TAG(i);
		DECLARE_TAG(iframe, src, srcdoc, name, sandbox, seamless, width, height);
		DECLARE_TAG(img, alt, src, ismap, usermap, width, height);
		DECLARE_TAG(input, accept, alt, autocomplete, autofocus, checked, disabled, form, formaction, formenctype, formmethod, formnovalidate, formtarget, height, list, max, maxlength, min, multiple, name, pattern, placeholder, readonly, required, size, src, step, type, value, width);
		DECLARE_TAG(ins, cite, datetime);
		DECLARE_TAG(kbd);
		DECLARE_TAG(keygen, autofocus, challenge, disabled, form, keytype, name);
		DECLARE_TAG(label, For, form);
		DECLARE_TAG(legend);
		DECLARE_TAG(li, value);
		DECLARE_TAG(link, href, hreflang, media, rel, type, sizes);
		DECLARE_TAG(mark);
		DECLARE_TAG(map, name);
		DECLARE_TAG(menu, type, label);
		DECLARE_TAG(meta, name, content, charset, http_equiv);
		DECLARE_TAG(meter, value, min, low, high, max, optimum);
		DECLARE_TAG(nav);
		DECLARE_TAG(noscript);
		DECLARE_TAG(object, data, type, name, usermap, form, width, height);
		DECLARE_TAG(ol, reversed, start);
		DECLARE_TAG(optgroup, disabled, label);
		DECLARE_TAG(option, disabled, label, selected, value);
		DECLARE_TAG(output, For, form, name);
		DECLARE_TAG(p);
		DECLARE_TAG(param, name, value);
		DECLARE_TAG(pre);
		DECLARE_TAG(progress, value, max);
		DECLARE_TAG(q, cite);
		DECLARE_TAG(ruby);
		DECLARE_TAG(rp);
		DECLARE_TAG(rt);
		DECLARE_TAG(samp);
		DECLARE_TAG(script, src, async, defer, type, charset);
		DECLARE_TAG(section);
		DECLARE_TAG(select, autofocus, disabled, form, multiple, name, size);
		DECLARE_TAG(small);
		DECLARE_TAG(source, src, type, media);
		DECLARE_TAG(span);
		DECLARE_TAG(strong);
		DECLARE_TAG(style, type, media, scoped);
		DECLARE_TAG(sub);
		DECLARE_TAG(summary);
		DECLARE_TAG(sup);
		DECLARE_TAG(table);
		DECLARE_TAG(tbody);
		DECLARE_TAG(td, colspan, rowspan, headers);
		DECLARE_TAG(textarea, autofocus, disabled, form, maxlength, name, placeholder, readonly, required, rows, cols, wrap);
		DECLARE_TAG(tfoot);
		DECLARE_TAG(th, colspan, rowspan, headers, scope);
		DECLARE_TAG(thead);
		DECLARE_TAG(time, datetime);
		DECLARE_TAG(title);
		DECLARE_TAG(tr);
		DECLARE_TAG(ul);
		DECLARE_TAG(var);
		DECLARE_TAG(video, src, poster, preload, autoplay, loop, controls, width, height);
		DECLARE_TAG(wbr);
	}
}

#endif /* TAGSTRUCTS_HPP_ */
