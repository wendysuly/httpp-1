/*************************
 *         htt++         *
 *************************
 * Tag Structures Module *
 *      Source File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#include "TagStructs.hpp"

//Unfortunately, this can't be delcared in the header, but the tag classes themselves have to be.
//So we have to declare each tag twice - once in the header, once here.
#define STATIC_TAG(tag) std::vector<std::string> tag::m_arg_names = std::vector<std::string>()

namespace httpp
{
	namespace Tags
	{
		void str_copy(char *dest, const char *src)
		{
			while( *src != '\0' )
				*dest++ = *src++;
			*dest = '\0';
		}

		void populate_args(std::vector<std::string> &v, std::string s)
		{
			if(!v.empty())
				return;
			std::string cur;
			int len = s.length();
			for(int i=0;i<=len;i++)
			{
				if(s[i] == ',')
				{
					v.push_back(cur);
					cur = "";
					continue;
				}
				if(s[i] == ' ')
					continue;
				cur += tolower(s[i]);
			}
		}

		const char * format_args(int i, int max, TagParam &p)
		{
			if(max == 0)
				return "";
			std::stringstream s;
			if(p != "")
				s << i << "\v" << p.str();
			return s.str().c_str();
		}

		std::string argify(std::vector<std::string> &v, const char *s)
		{
			static char cur[256];
			static char out[32768];
			static const char *c;
			out[0] = '\0';
			cur[0] = '\0';
			static unsigned int pos;
			static unsigned int cpos;
			pos = 0;
			cpos = 0;
			static int argnum;
			argnum = 0;
			for( ;*s != '\0';s++)
			{
				if(*s == '\v')
				{
					argnum = atoi(cur);
					cur[0] = '\0';
					cpos = 0;
					continue;
				}
				if(*s == '\a')
				{
					out[pos++] = ' ';

					c = v[argnum].c_str();
					while( *c != '\0' )
						out[pos++] = *(c++);

					out[pos++] = '=';
					out[pos++] = '\"';

					cur[cpos] = '\0';
					c = cur;
					while( *c != '\0' )
						out[pos++] = *(c++);

					out[pos++] = '\"';

					cur[0] = '\0';
					cpos = 0;
					continue;
				}
				cur[cpos++] = *s;
			}
			out[pos] = '\0';
			return out;
		}

		STATIC_TAG(a);
		STATIC_TAG(abbr);
		STATIC_TAG(address);
		STATIC_TAG(area);
		STATIC_TAG(article);
		STATIC_TAG(aside);
		STATIC_TAG(audio);
		STATIC_TAG(b);
		STATIC_TAG(base);
		STATIC_TAG(bb);
		STATIC_TAG(bdo);
		STATIC_TAG(blockquote);
		STATIC_TAG(body);
		STATIC_TAG(br);
		STATIC_TAG(button);
		STATIC_TAG(canvas);
		STATIC_TAG(caption);
		STATIC_TAG(cite);
		STATIC_TAG(code);
		STATIC_TAG(col);
		STATIC_TAG(colgroup);
		STATIC_TAG(command);
		STATIC_TAG(datagrid);
		STATIC_TAG(datalist);
		STATIC_TAG(dd);
		STATIC_TAG(del);
		STATIC_TAG(details);
		STATIC_TAG(dfn);
		STATIC_TAG(div);
		STATIC_TAG(dl);
		STATIC_TAG(dt);
		STATIC_TAG(em);
		STATIC_TAG(embed);
		STATIC_TAG(eventsource);
		STATIC_TAG(fieldset);
		STATIC_TAG(figcaption);
		STATIC_TAG(figure);
		STATIC_TAG(footer);
		STATIC_TAG(form);
		STATIC_TAG(h1);
		STATIC_TAG(h2);
		STATIC_TAG(h3);
		STATIC_TAG(h4);
		STATIC_TAG(h5);
		STATIC_TAG(h6);
		STATIC_TAG(head);
		STATIC_TAG(header);
		STATIC_TAG(hgroup);
		STATIC_TAG(hr);
		STATIC_TAG(html);
		STATIC_TAG(i);
		STATIC_TAG(iframe);
		STATIC_TAG(img);
		STATIC_TAG(input);
		STATIC_TAG(ins);
		STATIC_TAG(kbd);
		STATIC_TAG(keygen);
		STATIC_TAG(label);
		STATIC_TAG(legend);
		STATIC_TAG(li);
		STATIC_TAG(link);
		STATIC_TAG(mark);
		STATIC_TAG(map);
		STATIC_TAG(menu);
		STATIC_TAG(meta);
		STATIC_TAG(meter);
		STATIC_TAG(nav);
		STATIC_TAG(noscript);
		STATIC_TAG(object);
		STATIC_TAG(ol);
		STATIC_TAG(optgroup);
		STATIC_TAG(option);
		STATIC_TAG(output);
		STATIC_TAG(p);
		STATIC_TAG(param);
		STATIC_TAG(pre);
		STATIC_TAG(progress);
		STATIC_TAG(q);
		STATIC_TAG(ruby);
		STATIC_TAG(rp);
		STATIC_TAG(rt);
		STATIC_TAG(samp);
		STATIC_TAG(script);
		STATIC_TAG(section);
		STATIC_TAG(select);
		STATIC_TAG(small);
		STATIC_TAG(source);
		STATIC_TAG(span);
		STATIC_TAG(strong);
		STATIC_TAG(style);
		STATIC_TAG(sub);
		STATIC_TAG(summary);
		STATIC_TAG(sup);
		STATIC_TAG(table);
		STATIC_TAG(tbody);
		STATIC_TAG(td);
		STATIC_TAG(textarea);
		STATIC_TAG(tfoot);
		STATIC_TAG(th);
		STATIC_TAG(thead);
		STATIC_TAG(time);
		STATIC_TAG(title);
		STATIC_TAG(tr);
		STATIC_TAG(ul);
		STATIC_TAG(var);
		STATIC_TAG(video);
		STATIC_TAG(wbr);
	}
}
