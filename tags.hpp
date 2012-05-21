/*************************
 *         htt++         *
 *************************
 *       Tag Module      *
 *      Header File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#ifndef TAGS_HPP_
#define TAGS_HPP_

#include <iostream>

/*
 * Warning: This file contains a LOT of macros!
 * Unfortunately, while I know macros are often misused and present a number of issues, there's simply no way around this to accomplish what I'm trying to accomplish here.
 * In order to extend the C++ language to enable our html tags to fit nicely in them, we have to use these macros to make it happen.
 *
 * This does have two unfortunate drawbacks beyond what occurs with normal macros:
 *
 * 1) if tag names (such as "b") are used as variables in any header file included *after* this one, it'll cause a conflict.
 * As a result, the htt++ headers need to always be the last header file included in any project. (Boost libraries, in particular, tend to conflict.)
 *
 * 2) Any variables used to set tag attributes must be declared static (as our macros create local classes, which can only access variables from the enclosing
 * function if they are declared static or enum).
 *
 * However, despite those drawbacks, the result of this implementation is well worth the potential pitfalls. No other dynamic HTML language will allow syntax like this:
 *
 * Page(index)
 * {
 * 		static std::string msg = "Hello, world!";
 * 		static std::string loadmsg = "";
 * 		bool showAlert = True;
 * 		HTML
 * 		{
 * 			HEAD
 * 			{
 * 				xscript(src="foo.js");
 * 				$title(msg);
 * 			}
 * 			if(ShowAlert == True):
 * 				loadmsg = "alert(\""+msg+"\");";
 * 			else
 * 				loadmsg = "";
 * 			body(background="#FFFFFF" onload=loadmsg)
 * 			{
 * 				div(Class="bar" id="baz")
 * 				{
 * 					$span(msg, id="qux");
 * 				}
 * 			}
 * 		}
 * }
 *
 * The end result is a clean, readable language for creating fast, dynamic web pages, without requiring the need for any additional custom parsers or compilers.
 */


//Count the number of arguments in a variadic macro...
#define HTTPP_NARG(...) \
         HTTPP_NARG_(__VA_ARGS__,HTTPP_RSEQ_N())
#define HTTPP_NARG_(...) \
         HTTPP_ARG_N(__VA_ARGS__)
#define HTTPP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define HTTPP_RSEQ_N() \
         63,62,61,60,                  \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

/*
 * This is quite possibly the most important piece of the whole library: the tag builder.
 * This creates a temporary local class called tmp, inherited from a class nmed http::Tags::<tag name> (see TagStructs.hpp), and uses the variadic arguments to
 * set the desired attributes, and then passes a new instance of that struct to the setTag method of the Page class. The setTag function then calls the methods on the
 * tag class to create and print the tag properly.
 *
 * This all happens in a single-iteration do-while loop for scoping: since it's all in the loop, the name "tmp" is released after the class is created, allowing the same
 * tag to be used multiple times in the same scope.
 *
 * The constructor here takes a single char, because our argument counting fails when there are 0 args - so passing the first character of a stringified version of our
 * arguments list lets us determine whether or not we had any arguments passed. Calculating the number of arguments is important to keep the library performant.
 */
#define HTTPP_BUILD_TAG(tagname, ...)	do{ \
											struct tmp : public httpp::Tags::tagname \
											{ \
												tmp(char c) \
												{ \
													if(c == '\0') \
														m_num_args = 0; \
													else \
													{ \
														__VA_ARGS__; \
														m_num_args = HTTPP_NARG(__VA_ARGS__); \
													} \
												} \
												~tmp() { } \
											}; \
											setTag(new tmp(#__VA_ARGS__[0])); \
										} while(false)

// These macros are used to call HTTPP_BUILD_TAG in various ways:

/*
 * This one is the "Basic" tag. This is the function that allows us to use tags as code blocks with proper C++ scoping that translate properly to HTML syntax.
 * The for loop here calls the function "end_tag()," which prints a closing tag for the tag that got passed (it keeps track of the tag heirarchy so that it can
 * close the tags properly). This function then always returns false, so our for loop only executes once. Putting our code inside a single-iteration for loop
 * guarantees proper scoping.
 */
#define HTTPP_TAG(tagname, ...) HTTPP_BUILD_TAG(tagname, __VA_ARGS__); tag(#tagname); for(bool b=true;b;b=end_tag())

/*
 * This creates an inline tag. Unlike the HTTP_TAG macro, this doesn't create a block, but instead just accepts a string as its first argument, which will be
 * printed in between the opening and closing tags on the same line. I.e.:
 * 		$strong("foo");
 * produces:
 * 		<strong>foo</strong>
 */

#define HTTPP_I_TAG(str, tagname, ...) [&](){HTTPP_BUILD_TAG(tagname, __VA_ARGS__); $(make_inline_tag(str, #tagname));}()

/*
 * This creates an inline tag that returns a std::string containing the generated tag. Works the same as the above otherwise.
 */

#define INLINE_TAG(str, tagname, ...) [&](){HTTPP_BUILD_TAG(tagname, __VA_ARGS__); return make_inline_tag(str, #tagname);}()

/*
 * This creates an xhtml self-closing tag of the following format:
 * 		<tag attrs.... />
 */
#define HTTP_X_TAG(tagname, ...) [&](){HTTPP_BUILD_TAG(tagname, __VA_ARGS__); make_x_tag(#tagname);}()

#define REDEFINE_TAGS() #include <tags.hpp>

#endif

//Outside preprocessor ifchecks for easy folding.
//Inside preprocessor ifchecks enable the source file to be re-imported if something needs to be temporarily undefined, without having to redefine everything.

//Normal tags. Convention: The tag name, in lower case, with arguments. "tagname(...)"
#if true
	#ifndef a
		#define a(...) HTTPP_TAG(a, __VA_ARGS__)
	#endif
	#ifndef abbr
		#define abbr(...) HTTPP_TAG(abbr, __VA_ARGS__)
	#endif
	#ifndef address
		#define address(...) HTTPP_TAG(address, __VA_ARGS__)
	#endif
	#ifndef area
		#define area(...) HTTPP_TAG(area, __VA_ARGS__)
	#endif
	#ifndef article
		#define article(...) HTTPP_TAG(article, __VA_ARGS__)
	#endif
	#ifndef aside
		#define aside(...) HTTPP_TAG(aside, __VA_ARGS__)
	#endif
	#ifndef audio
		#define audio(...) HTTPP_TAG(audio, __VA_ARGS__)
	#endif
	#ifndef b
		#define b(...) HTTPP_TAG(b, __VA_ARGS__)
	#endif
	#ifndef base
		#define base(...) HTTPP_TAG(base, __VA_ARGS__)
	#endif
	#ifndef bb
		#define bb(...) HTTPP_TAG(bb, __VA_ARGS__)
	#endif
	#ifndef bdo
		#define bdo(...) HTTPP_TAG(bdo, __VA_ARGS__)
	#endif
	#ifndef blockquote
		#define blockquote(...) HTTPP_TAG(blockquote, __VA_ARGS__)
	#endif
	#ifndef body
		#define body(...) HTTPP_TAG(body, __VA_ARGS__)
	#endif
	#ifndef br
		#define br(...) HTTPP_TAG(br, __VA_ARGS__)
	#endif
	#ifndef button
		#define button(...) HTTPP_TAG(button, __VA_ARGS__)
	#endif
	#ifndef canvas
		#define canvas(...) HTTPP_TAG(canvas, __VA_ARGS__)
	#endif
	#ifndef caption
		#define caption(...) HTTPP_TAG(caption, __VA_ARGS__)
	#endif
	#ifndef cite
		#define cite(...) HTTPP_TAG(cite, __VA_ARGS__)
	#endif
	#ifndef code
		#define code(...) HTTPP_TAG(code, __VA_ARGS__)
	#endif
	#ifndef col
		#define col(...) HTTPP_TAG(col, __VA_ARGS__)
	#endif
	#ifndef colgroup
		#define colgroup(...) HTTPP_TAG(colgroup, __VA_ARGS__)
	#endif
	#ifndef command
		#define command(...) HTTPP_TAG(command, __VA_ARGS__)
	#endif
	#ifndef datagrid
		#define datagrid(...) HTTPP_TAG(datagrid, __VA_ARGS__)
	#endif
	#ifndef datalist
		#define datalist(...) HTTPP_TAG(datalist, __VA_ARGS__)
	#endif
	#ifndef dd
		#define dd(...) HTTPP_TAG(dd, __VA_ARGS__)
	#endif
	#ifndef del
		#define del(...) HTTPP_TAG(del, __VA_ARGS__)
	#endif
	#ifndef details
		#define details(...) HTTPP_TAG(details, __VA_ARGS__)
	#endif
	#ifndef dfn
		#define dfn(...) HTTPP_TAG(dfn, __VA_ARGS__)
	#endif
	#ifndef div
		#define div(...) HTTPP_TAG(div, __VA_ARGS__)
	#endif
	#ifndef dl
		#define dl(...) HTTPP_TAG(dl, __VA_ARGS__)
	#endif
	#ifndef dt
		#define dt(...) HTTPP_TAG(dt, __VA_ARGS__)
	#endif
	#ifndef em
		#define em(...) HTTPP_TAG(em, __VA_ARGS__)
	#endif
	#ifndef embed
		#define embed(...) HTTPP_TAG(embed, __VA_ARGS__)
	#endif
	#ifndef eventsource
		#define eventsource(...) HTTPP_TAG(eventsource, __VA_ARGS__)
	#endif
	#ifndef fieldset
		#define fieldset(...) HTTPP_TAG(fieldset, __VA_ARGS__)
	#endif
	#ifndef figcaption
		#define figcaption(...) HTTPP_TAG(figcaption, __VA_ARGS__)
	#endif
	#ifndef figure
		#define figure(...) HTTPP_TAG(figure, __VA_ARGS__)
	#endif
	#ifndef footer
		#define footer(...) HTTPP_TAG(footer, __VA_ARGS__)
	#endif
	#ifndef form
		#define form(...) HTTPP_TAG(form, __VA_ARGS__)
	#endif
	#ifndef h1
		#define h1(...) HTTPP_TAG(h1, __VA_ARGS__)
	#endif
	#ifndef h2
		#define h2(...) HTTPP_TAG(h2, __VA_ARGS__)
	#endif
	#ifndef h3
		#define h3(...) HTTPP_TAG(h3, __VA_ARGS__)
	#endif
	#ifndef h4
		#define h4(...) HTTPP_TAG(h4, __VA_ARGS__)
	#endif
	#ifndef h5
		#define h5(...) HTTPP_TAG(h5, __VA_ARGS__)
	#endif
	#ifndef h6
		#define h6(...) HTTPP_TAG(h6, __VA_ARGS__)
	#endif
	#ifndef head
		#define head(...) HTTPP_TAG(head, __VA_ARGS__)
	#endif
	#ifndef header
		#define header(...) HTTPP_TAG(header, __VA_ARGS__)
	#endif
	#ifndef hgroup
		#define hgroup(...) HTTPP_TAG(hgroup, __VA_ARGS__)
	#endif
	#ifndef hr
		#define hr(...) HTTPP_TAG(hr, __VA_ARGS__)
	#endif
	#ifndef html
		#define html(...) HTTPP_TAG(html, __VA_ARGS__)
	#endif
	#ifndef i
		#define i(...) HTTPP_TAG(i, __VA_ARGS__)
	#endif
	#ifndef iframe
		#define iframe(...) HTTPP_TAG(iframe, __VA_ARGS__)
	#endif
	#ifndef img
		#define img(...) HTTPP_TAG(img, __VA_ARGS__)
	#endif
	#ifndef input
		#define input(...) HTTPP_TAG(input, __VA_ARGS__)
	#endif
	#ifndef ins
		#define ins(...) HTTPP_TAG(ins, __VA_ARGS__)
	#endif
	#ifndef kbd
		#define kbd(...) HTTPP_TAG(kbd, __VA_ARGS__)
	#endif
	#ifndef keygen
		#define keygen(...) HTTPP_TAG(keygen, __VA_ARGS__)
	#endif
	#ifndef label
		#define label(...) HTTPP_TAG(label, __VA_ARGS__)
	#endif
	#ifndef legend
		#define legend(...) HTTPP_TAG(legend, __VA_ARGS__)
	#endif
	#ifndef li
		#define li(...) HTTPP_TAG(li, __VA_ARGS__)
	#endif
	#ifndef link
		#define link(...) HTTPP_TAG(link, __VA_ARGS__)
	#endif
	#ifndef mark
		#define mark(...) HTTPP_TAG(mark, __VA_ARGS__)
	#endif
	#ifndef map
		#define map(...) HTTPP_TAG(map, __VA_ARGS__)
	#endif
	#ifndef menu
		#define menu(...) HTTPP_TAG(menu, __VA_ARGS__)
	#endif
	#ifndef meta
		#define meta(...) HTTPP_TAG(meta, __VA_ARGS__)
	#endif
	#ifndef meter
		#define meter(...) HTTPP_TAG(meter, __VA_ARGS__)
	#endif
	#ifndef nav
		#define nav(...) HTTPP_TAG(nav, __VA_ARGS__)
	#endif
	#ifndef noscript
		#define noscript(...) HTTPP_TAG(noscript, __VA_ARGS__)
	#endif
	#ifndef object
		#define object(...) HTTPP_TAG(object, __VA_ARGS__)
	#endif
	#ifndef ol
		#define ol(...) HTTPP_TAG(ol, __VA_ARGS__)
	#endif
	#ifndef optgroup
		#define optgroup(...) HTTPP_TAG(optgroup, __VA_ARGS__)
	#endif
	#ifndef option
		#define option(...) HTTPP_TAG(option, __VA_ARGS__)
	#endif
	#ifndef output
		#define output(...) HTTPP_TAG(output, __VA_ARGS__)
	#endif
	#ifndef p
		#define p(...) HTTPP_TAG(p, __VA_ARGS__)
	#endif
	#ifndef param
		#define param(...) HTTPP_TAG(param, __VA_ARGS__)
	#endif
	#ifndef pre
		#define pre(...) HTTPP_TAG(pre, __VA_ARGS__)
	#endif
	#ifndef progress
		#define progress(...) HTTPP_TAG(progress, __VA_ARGS__)
	#endif
	#ifndef q
		#define q(...) HTTPP_TAG(q, __VA_ARGS__)
	#endif
	#ifndef ruby
		#define ruby(...) HTTPP_TAG(ruby, __VA_ARGS__)
	#endif
	#ifndef rp
		#define rp(...) HTTPP_TAG(rp, __VA_ARGS__)
	#endif
	#ifndef rt
		#define rt(...) HTTPP_TAG(rt, __VA_ARGS__)
	#endif
	#ifndef samp
		#define samp(...) HTTPP_TAG(samp, __VA_ARGS__)
	#endif
	#ifndef script
		#define script(...) HTTPP_TAG(script, __VA_ARGS__)
	#endif
	#ifndef section
		#define section(...) HTTPP_TAG(section, __VA_ARGS__)
	#endif
	#ifndef select
		#define select(...) HTTPP_TAG(select, __VA_ARGS__)
	#endif
	#ifndef small
		#define small(...) HTTPP_TAG(small, __VA_ARGS__)
	#endif
	#ifndef source
		#define source(...) HTTPP_TAG(source, __VA_ARGS__)
	#endif
	#ifndef span
		#define span(...) HTTPP_TAG(span, __VA_ARGS__)
	#endif
	#ifndef strong
		#define strong(...) HTTPP_TAG(strong, __VA_ARGS__)
	#endif
	#ifndef style
		#define style(...) HTTPP_TAG(style, __VA_ARGS__)
	#endif
	#ifndef sub
		#define sub(...) HTTPP_TAG(sub, __VA_ARGS__)
	#endif
	#ifndef summary
		#define summary(...) HTTPP_TAG(summary, __VA_ARGS__)
	#endif
	#ifndef sup
		#define sup(...) HTTPP_TAG(sup, __VA_ARGS__)
	#endif
	#ifndef table
		#define table(...) HTTPP_TAG(table, __VA_ARGS__)
	#endif
	#ifndef tbody
		#define tbody(...) HTTPP_TAG(tbody, __VA_ARGS__)
	#endif
	#ifndef td
		#define td(...) HTTPP_TAG(td, __VA_ARGS__)
	#endif
	#ifndef textarea
		#define textarea(...) HTTPP_TAG(textarea, __VA_ARGS__)
	#endif
	#ifndef tfoot
		#define tfoot(...) HTTPP_TAG(tfoot, __VA_ARGS__)
	#endif
	#ifndef th
		#define th(...) HTTPP_TAG(th, __VA_ARGS__)
	#endif
	#ifndef thead
		#define thead(...) HTTPP_TAG(thead, __VA_ARGS__)
	#endif
	#ifndef time
		#define time(...) HTTPP_TAG(time, __VA_ARGS__)
	#endif
	#ifndef title
		#define title(...) HTTPP_TAG(title, __VA_ARGS__)
	#endif
	#ifndef tr
		#define tr(...) HTTPP_TAG(tr, __VA_ARGS__)
	#endif
	#ifndef ul
		#define ul(...) HTTPP_TAG(ul, __VA_ARGS__)
	#endif
	#ifndef var
		#define var(...) HTTPP_TAG(var, __VA_ARGS__)
	#endif
	#ifndef video
		#define video(...) HTTPP_TAG(video, __VA_ARGS__)
	#endif
	#ifndef wbr
		#define wbr(...) HTTPP_TAG(wbr, __VA_ARGS__)
	#endif
#endif

//Normal tags without arguments. No empty parens are required when using these. Convention: The tag name, in all capitals. "TAGNAME"
#if true
	#ifndef A
		#define A a()
	#endif
	#ifndef ABBR
		#define ABBR abbr()
	#endif
	#ifndef ADDRESS
		#define ADDRESS address()
	#endif
	#ifndef AREA
		#define AREA area()
	#endif
	#ifndef ARTICLE
		#define ARTICLE article()
	#endif
	#ifndef ASIDE
		#define ASIDE aside()
	#endif
	#ifndef AUDIO
		#define AUDIO audio()
	#endif
	#ifndef B
		#define B b()
	#endif
	#ifndef BASE
		#define BASE base()
	#endif
	#ifndef BB
		#define BB bb()
	#endif
	#ifndef BDO
		#define BDO bdo()
	#endif
	#ifndef BLOCKQUOTE
		#define BLOCKQUOTE blockquote()
	#endif
	#ifndef BODY
		#define BODY body()
	#endif
	#ifndef BR
		#define BR br()
	#endif
	#ifndef BUTTON
		#define BUTTON button()
	#endif
	#ifndef CANVAS
		#define CANVAS canvas()
	#endif
	#ifndef CAPTION
		#define CAPTION caption()
	#endif
	#ifndef CITE
		#define CITE cite()
	#endif
	#ifndef CODE
		#define CODE code()
	#endif
	#ifndef COL
		#define COL col()
	#endif
	#ifndef COLGROUP
		#define COLGROUP colgroup()
	#endif
	#ifndef COMMAND
		#define COMMAND command()
	#endif
	#ifndef DATAGRID
		#define DATAGRID datagrid()
	#endif
	#ifndef DATALIST
		#define DATALIST datalist()
	#endif
	#ifndef DD
		#define DD dd()
	#endif
	#ifndef DEL
		#define DEL del()
	#endif
	#ifndef DETAILS
		#define DETAILS details()
	#endif
	#ifndef DFN
		#define DFN dfn()
	#endif
	#ifndef DIV
		#define DIV div()
	#endif
	#ifndef DL
		#define DL dl()
	#endif
	#ifndef DT
		#define DT dt()
	#endif
	#ifndef EM
		#define EM em()
	#endif
	#ifndef EMBED
		#define EMBED embed()
	#endif
	#ifndef EVENTSOURCE
		#define EVENTSOURCE eventsource()
	#endif
	#ifndef FIELDSET
		#define FIELDSET fieldset()
	#endif
	#ifndef FIGCAPTION
		#define FIGCAPTION figcaption()
	#endif
	#ifndef FIGURE
		#define FIGURE figure()
	#endif
	#ifndef FOOTER
		#define FOOTER footer()
	#endif
	#ifndef FORM
		#define FORM form()
	#endif
	#ifndef H1
		#define H1 h1()
	#endif
	#ifndef H2
		#define H2 h2()
	#endif
	#ifndef H3
		#define H3 h3()
	#endif
	#ifndef H4
		#define H4 h4()
	#endif
	#ifndef H5
		#define H5 h5()
	#endif
	#ifndef H6
		#define H6 h6()
	#endif
	#ifndef HEAD
		#define HEAD head()
	#endif
	#ifndef HEADER
		#define HEADER header()
	#endif
	#ifndef HGROUP
		#define HGROUP hgroup()
	#endif
	#ifndef HR
		#define HR hr()
	#endif
	#ifndef HTML
		#define HTML html()
	#endif
	#ifndef I
		#define I i()
	#endif
	#ifndef IFRAME
		#define IFRAME iframe()
	#endif
	#ifndef IMG
		#define IMG img()
	#endif
	#ifndef INPUT
		#define INPUT input()
	#endif
	#ifndef INS
		#define INS ins()
	#endif
	#ifndef KBD
		#define KBD kbd()
	#endif
	#ifndef KEYGEN
		#define KEYGEN keygen()
	#endif
	#ifndef LABEL
		#define LABEL label()
	#endif
	#ifndef LEGEND
		#define LEGEND legend()
	#endif
	#ifndef LI
		#define LI li()
	#endif
	#ifndef LINK
		#define LINK link()
	#endif
	#ifndef MARK
		#define MARK mark()
	#endif
	#ifndef MAP
		#define MAP map()
	#endif
	#ifndef MENU
		#define MENU menu()
	#endif
	#ifndef META
		#define META meta()
	#endif
	#ifndef METER
		#define METER meter()
	#endif
	#ifndef NAV
		#define NAV nav()
	#endif
	#ifndef NOSCRIPT
		#define NOSCRIPT noscript()
	#endif
	#ifndef OBJECT
		#define OBJECT object()
	#endif
	#ifndef OL
		#define OL ol()
	#endif
	#ifndef OPTGROUP
		#define OPTGROUP optgroup()
	#endif
	#ifndef OPTION
		#define OPTION option()
	#endif
	#ifndef OUTPUT
		#define OUTPUT output()
	#endif
	#ifndef P
		#define P p()
	#endif
	#ifndef PARAM
		#define PARAM param()
	#endif
	#ifndef PRE
		#define PRE pre()
	#endif
	#ifndef PROGRESS
		#define PROGRESS progress()
	#endif
	#ifndef Q
		#define Q q()
	#endif
	#ifndef RUBY
		#define RUBY ruby()
	#endif
	#ifndef RP
		#define RP rp()
	#endif
	#ifndef RT
		#define RT rt()
	#endif
	#ifndef SAMP
		#define SAMP samp()
	#endif
	#ifndef SCRIPT
		#define SCRIPT script()
	#endif
	#ifndef SECTION
		#define SECTION section()
	#endif
	#ifndef SELECT
		#define SELECT select()
	#endif
	#ifndef SMALL
		#define SMALL small()
	#endif
	#ifndef SOURCE
		#define SOURCE source()
	#endif
	#ifndef SPAN
		#define SPAN span()
	#endif
	#ifndef STRONG
		#define STRONG strong()
	#endif
	#ifndef STYLE
		#define STYLE style()
	#endif
	#ifndef SUB
		#define SUB sub()
	#endif
	#ifndef SUMMARY
		#define SUMMARY summary()
	#endif
	#ifndef SUP
		#define SUP sup()
	#endif
	#ifndef TABLE
		#define TABLE table()
	#endif
	#ifndef TBODY
		#define TBODY tbody()
	#endif
	#ifndef TD
		#define TD td()
	#endif
	#ifndef TEXTAREA
		#define TEXTAREA textarea()
	#endif
	#ifndef TFOOT
		#define TFOOT tfoot()
	#endif
	#ifndef TH
		#define TH th()
	#endif
	#ifndef THEAD
		#define THEAD thead()
	#endif
	#ifndef TIME
		#define TIME time()
	#endif
	#ifndef TITLE
		#define TITLE title()
	#endif
	#ifndef TR
		#define TR tr()
	#endif
	#ifndef UL
		#define UL ul()
	#endif
	#ifndef VAR
		#define VAR var()
	#endif
	#ifndef VIDEO
		#define VIDEO video()
	#endif
	#ifndef WBR
		#define WBR wbr()
	#endif
#endif

//Inline tags printed directly. Convention: $tagname(str, ...)
#if true
	#ifndef $a
		#define $a(str, ...) HTTPP_I_TAG(str, a, __VA_ARGS__)
	#endif
	#ifndef $abbr
		#define $abbr(str, ...) HTTPP_I_TAG(str, abbr, __VA_ARGS__)
	#endif
	#ifndef $address
		#define $address(str, ...) HTTPP_I_TAG(str, address, __VA_ARGS__)
	#endif
	#ifndef $area
		#define $area(str, ...) HTTPP_I_TAG(str, area, __VA_ARGS__)
	#endif
	#ifndef $article
		#define $article(str, ...) HTTPP_I_TAG(str, article, __VA_ARGS__)
	#endif
	#ifndef $aside
		#define $aside(str, ...) HTTPP_I_TAG(str, aside, __VA_ARGS__)
	#endif
	#ifndef $audio
		#define $audio(str, ...) HTTPP_I_TAG(str, audio, __VA_ARGS__)
	#endif
	#ifndef $b
		#define $b(str, ...) HTTPP_I_TAG(str, b, __VA_ARGS__)
	#endif
	#ifndef $base
		#define $base(str, ...) HTTPP_I_TAG(str, base, __VA_ARGS__)
	#endif
	#ifndef $bb
		#define $bb(str, ...) HTTPP_I_TAG(str, bb, __VA_ARGS__)
	#endif
	#ifndef $bdo
		#define $bdo(str, ...) HTTPP_I_TAG(str, bdo, __VA_ARGS__)
	#endif
	#ifndef $blockquote
		#define $blockquote(str, ...) HTTPP_I_TAG(str, blockquote, __VA_ARGS__)
	#endif
	#ifndef $body
		#define $body(str, ...) HTTPP_I_TAG(str, body, __VA_ARGS__)
	#endif
	#ifndef $br
		#define $br(str, ...) HTTPP_I_TAG(str, br, __VA_ARGS__)
	#endif
	#ifndef $button
		#define $button(str, ...) HTTPP_I_TAG(str, button, __VA_ARGS__)
	#endif
	#ifndef $canvas
		#define $canvas(str, ...) HTTPP_I_TAG(str, canvas, __VA_ARGS__)
	#endif
	#ifndef $caption
		#define $caption(str, ...) HTTPP_I_TAG(str, caption, __VA_ARGS__)
	#endif
	#ifndef $cite
		#define $cite(str, ...) HTTPP_I_TAG(str, cite, __VA_ARGS__)
	#endif
	#ifndef $code
		#define $code(str, ...) HTTPP_I_TAG(str, code, __VA_ARGS__)
	#endif
	#ifndef $col
		#define $col(str, ...) HTTPP_I_TAG(str, col, __VA_ARGS__)
	#endif
	#ifndef $colgroup
		#define $colgroup(str, ...) HTTPP_I_TAG(str, colgroup, __VA_ARGS__)
	#endif
	#ifndef $command
		#define $command(str, ...) HTTPP_I_TAG(str, command, __VA_ARGS__)
	#endif
	#ifndef $datagrid
		#define $datagrid(str, ...) HTTPP_I_TAG(str, datagrid, __VA_ARGS__)
	#endif
	#ifndef $datalist
		#define $datalist(str, ...) HTTPP_I_TAG(str, datalist, __VA_ARGS__)
	#endif
	#ifndef $dd
		#define $dd(str, ...) HTTPP_I_TAG(str, dd, __VA_ARGS__)
	#endif
	#ifndef $del
		#define $del(str, ...) HTTPP_I_TAG(str, del, __VA_ARGS__)
	#endif
	#ifndef $details
		#define $details(str, ...) HTTPP_I_TAG(str, details, __VA_ARGS__)
	#endif
	#ifndef $dfn
		#define $dfn(str, ...) HTTPP_I_TAG(str, dfn, __VA_ARGS__)
	#endif
	#ifndef $div
		#define $div(str, ...) HTTPP_I_TAG(str, div, __VA_ARGS__)
	#endif
	#ifndef $dl
		#define $dl(str, ...) HTTPP_I_TAG(str, dl, __VA_ARGS__)
	#endif
	#ifndef $dt
		#define $dt(str, ...) HTTPP_I_TAG(str, dt, __VA_ARGS__)
	#endif
	#ifndef $em
		#define $em(str, ...) HTTPP_I_TAG(str, em, __VA_ARGS__)
	#endif
	#ifndef $embed
		#define $embed(str, ...) HTTPP_I_TAG(str, embed, __VA_ARGS__)
	#endif
	#ifndef $eventsource
		#define $eventsource(str, ...) HTTPP_I_TAG(str, eventsource, __VA_ARGS__)
	#endif
	#ifndef $fieldset
		#define $fieldset(str, ...) HTTPP_I_TAG(str, fieldset, __VA_ARGS__)
	#endif
	#ifndef $figcaption
		#define $figcaption(str, ...) HTTPP_I_TAG(str, figcaption, __VA_ARGS__)
	#endif
	#ifndef $figure
		#define $figure(str, ...) HTTPP_I_TAG(str, figure, __VA_ARGS__)
	#endif
	#ifndef $footer
		#define $footer(str, ...) HTTPP_I_TAG(str, footer, __VA_ARGS__)
	#endif
	#ifndef $form
		#define $form(str, ...) HTTPP_I_TAG(str, form, __VA_ARGS__)
	#endif
	#ifndef $h1
		#define $h1(str, ...) HTTPP_I_TAG(str, h1, __VA_ARGS__)
	#endif
	#ifndef $h2
		#define $h2(str, ...) HTTPP_I_TAG(str, h2, __VA_ARGS__)
	#endif
	#ifndef $h3
		#define $h3(str, ...) HTTPP_I_TAG(str, h3, __VA_ARGS__)
	#endif
	#ifndef $h4
		#define $h4(str, ...) HTTPP_I_TAG(str, h4, __VA_ARGS__)
	#endif
	#ifndef $h5
		#define $h5(str, ...) HTTPP_I_TAG(str, h5, __VA_ARGS__)
	#endif
	#ifndef $h6
		#define $h6(str, ...) HTTPP_I_TAG(str, h6, __VA_ARGS__)
	#endif
	#ifndef $head
		#define $head(str, ...) HTTPP_I_TAG(str, head, __VA_ARGS__)
	#endif
	#ifndef $header
		#define $header(str, ...) HTTPP_I_TAG(str, header, __VA_ARGS__)
	#endif
	#ifndef $hgroup
		#define $hgroup(str, ...) HTTPP_I_TAG(str, hgroup, __VA_ARGS__)
	#endif
	#ifndef $hr
		#define $hr(str, ...) HTTPP_I_TAG(str, hr, __VA_ARGS__)
	#endif
	#ifndef $html
		#define $html(str, ...) HTTPP_I_TAG(str, html, __VA_ARGS__)
	#endif
	#ifndef $i
		#define $i(str, ...) HTTPP_I_TAG(str, i, __VA_ARGS__)
	#endif
	#ifndef $iframe
		#define $iframe(str, ...) HTTPP_I_TAG(str, iframe, __VA_ARGS__)
	#endif
	#ifndef $img
		#define $img(str, ...) HTTPP_I_TAG(str, img, __VA_ARGS__)
	#endif
	#ifndef $input
		#define $input(str, ...) HTTPP_I_TAG(str, input, __VA_ARGS__)
	#endif
	#ifndef $ins
		#define $ins(str, ...) HTTPP_I_TAG(str, ins, __VA_ARGS__)
	#endif
	#ifndef $kbd
		#define $kbd(str, ...) HTTPP_I_TAG(str, kbd, __VA_ARGS__)
	#endif
	#ifndef $keygen
		#define $keygen(str, ...) HTTPP_I_TAG(str, keygen, __VA_ARGS__)
	#endif
	#ifndef $label
		#define $label(str, ...) HTTPP_I_TAG(str, label, __VA_ARGS__)
	#endif
	#ifndef $legend
		#define $legend(str, ...) HTTPP_I_TAG(str, legend, __VA_ARGS__)
	#endif
	#ifndef $li
		#define $li(str, ...) HTTPP_I_TAG(str, li, __VA_ARGS__)
	#endif
	#ifndef $link
		#define $link(str, ...) HTTPP_I_TAG(str, link, __VA_ARGS__)
	#endif
	#ifndef $mark
		#define $mark(str, ...) HTTPP_I_TAG(str, mark, __VA_ARGS__)
	#endif
	#ifndef $map
		#define $map(str, ...) HTTPP_I_TAG(str, map, __VA_ARGS__)
	#endif
	#ifndef $menu
		#define $menu(str, ...) HTTPP_I_TAG(str, menu, __VA_ARGS__)
	#endif
	#ifndef $meta
		#define $meta(str, ...) HTTPP_I_TAG(str, meta, __VA_ARGS__)
	#endif
	#ifndef $meter
		#define $meter(str, ...) HTTPP_I_TAG(str, meter, __VA_ARGS__)
	#endif
	#ifndef $nav
		#define $nav(str, ...) HTTPP_I_TAG(str, nav, __VA_ARGS__)
	#endif
	#ifndef $noscript
		#define $noscript(str, ...) HTTPP_I_TAG(str, noscript, __VA_ARGS__)
	#endif
	#ifndef $object
		#define $object(str, ...) HTTPP_I_TAG(str, object, __VA_ARGS__)
	#endif
	#ifndef $ol
		#define $ol(str, ...) HTTPP_I_TAG(str, ol, __VA_ARGS__)
	#endif
	#ifndef $optgroup
		#define $optgroup(str, ...) HTTPP_I_TAG(str, optgroup, __VA_ARGS__)
	#endif
	#ifndef $option
		#define $option(str, ...) HTTPP_I_TAG(str, option, __VA_ARGS__)
	#endif
	#ifndef $output
		#define $output(str, ...) HTTPP_I_TAG(str, output, __VA_ARGS__)
	#endif
	#ifndef $p
		#define $p(str, ...) HTTPP_I_TAG(str, p, __VA_ARGS__)
	#endif
	#ifndef $param
		#define $param(str, ...) HTTPP_I_TAG(str, param, __VA_ARGS__)
	#endif
	#ifndef $pre
		#define $pre(str, ...) HTTPP_I_TAG(str, pre, __VA_ARGS__)
	#endif
	#ifndef $progress
		#define $progress(str, ...) HTTPP_I_TAG(str, progress, __VA_ARGS__)
	#endif
	#ifndef $q
		#define $q(str, ...) HTTPP_I_TAG(str, q, __VA_ARGS__)
	#endif
	#ifndef $ruby
		#define $ruby(str, ...) HTTPP_I_TAG(str, ruby, __VA_ARGS__)
	#endif
	#ifndef $rp
		#define $rp(str, ...) HTTPP_I_TAG(str, rp, __VA_ARGS__)
	#endif
	#ifndef $rt
		#define $rt(str, ...) HTTPP_I_TAG(str, rt, __VA_ARGS__)
	#endif
	#ifndef $samp
		#define $samp(str, ...) HTTPP_I_TAG(str, samp, __VA_ARGS__)
	#endif
	#ifndef $script
		#define $script(str, ...) HTTPP_I_TAG(str, script, __VA_ARGS__)
	#endif
	#ifndef $section
		#define $section(str, ...) HTTPP_I_TAG(str, section, __VA_ARGS__)
	#endif
	#ifndef $select
		#define $select(str, ...) HTTPP_I_TAG(str, select, __VA_ARGS__)
	#endif
	#ifndef $small
		#define $small(str, ...) HTTPP_I_TAG(str, small, __VA_ARGS__)
	#endif
	#ifndef $source
		#define $source(str, ...) HTTPP_I_TAG(str, source, __VA_ARGS__)
	#endif
	#ifndef $span
		#define $span(str, ...) HTTPP_I_TAG(str, span, __VA_ARGS__)
	#endif
	#ifndef $strong
		#define $strong(str, ...) HTTPP_I_TAG(str, strong, __VA_ARGS__)
	#endif
	#ifndef $style
		#define $style(str, ...) HTTPP_I_TAG(str, style, __VA_ARGS__)
	#endif
	#ifndef $sub
		#define $sub(str, ...) HTTPP_I_TAG(str, sub, __VA_ARGS__)
	#endif
	#ifndef $summary
		#define $summary(str, ...) HTTPP_I_TAG(str, summary, __VA_ARGS__)
	#endif
	#ifndef $sup
		#define $sup(str, ...) HTTPP_I_TAG(str, sup, __VA_ARGS__)
	#endif
	#ifndef $table
		#define $table(str, ...) HTTPP_I_TAG(str, table, __VA_ARGS__)
	#endif
	#ifndef $tbody
		#define $tbody(str, ...) HTTPP_I_TAG(str, tbody, __VA_ARGS__)
	#endif
	#ifndef $td
		#define $td(str, ...) HTTPP_I_TAG(str, td, __VA_ARGS__)
	#endif
	#ifndef $textarea
		#define $textarea(str, ...) HTTPP_I_TAG(str, textarea, __VA_ARGS__)
	#endif
	#ifndef $tfoot
		#define $tfoot(str, ...) HTTPP_I_TAG(str, tfoot, __VA_ARGS__)
	#endif
	#ifndef $th
		#define $th(str, ...) HTTPP_I_TAG(str, th, __VA_ARGS__)
	#endif
	#ifndef $thead
		#define $thead(str, ...) HTTPP_I_TAG(str, thead, __VA_ARGS__)
	#endif
	#ifndef $time
		#define $time(str, ...) HTTPP_I_TAG(str, time, __VA_ARGS__)
	#endif
	#ifndef $title
		#define $title(str, ...) HTTPP_I_TAG(str, title, __VA_ARGS__)
	#endif
	#ifndef $tr
		#define $tr(str, ...) HTTPP_I_TAG(str, tr, __VA_ARGS__)
	#endif
	#ifndef $ul
		#define $ul(str, ...) HTTPP_I_TAG(str, ul, __VA_ARGS__)
	#endif
	#ifndef $var
		#define $var(str, ...) HTTPP_I_TAG(str, var, __VA_ARGS__)
	#endif
	#ifndef $video
		#define $video(str, ...) HTTPP_I_TAG(str, video, __VA_ARGS__)
	#endif
	#ifndef $wbr
		#define $wbr(str, ...) HTTPP_I_TAG(str, wbr, __VA_ARGS__)
	#endif
#endif

//Inline tags returning std::string for use in format strings. Convention: $$tagname(str, ...)
#if true
	#ifndef $$a
		#define $$a(str, ...) INLINE_TAG(str, a, __VA_ARGS__)
	#endif
	#ifndef $$abbr
		#define $$abbr(str, ...) INLINE_TAG(str, abbr, __VA_ARGS__)
	#endif
	#ifndef $$address
		#define $$address(str, ...) INLINE_TAG(str, address, __VA_ARGS__)
	#endif
	#ifndef $$area
		#define $$area(str, ...) INLINE_TAG(str, area, __VA_ARGS__)
	#endif
	#ifndef $$article
		#define $$article(str, ...) INLINE_TAG(str, article, __VA_ARGS__)
	#endif
	#ifndef $$aside
		#define $$aside(str, ...) INLINE_TAG(str, aside, __VA_ARGS__)
	#endif
	#ifndef $$audio
		#define $$audio(str, ...) INLINE_TAG(str, audio, __VA_ARGS__)
	#endif
	#ifndef $$b
		#define $$b(str, ...) INLINE_TAG(str, b, __VA_ARGS__)
	#endif
	#ifndef $$base
		#define $$base(str, ...) INLINE_TAG(str, base, __VA_ARGS__)
	#endif
	#ifndef $$bb
		#define $$bb(str, ...) INLINE_TAG(str, bb, __VA_ARGS__)
	#endif
	#ifndef $$bdo
		#define $$bdo(str, ...) INLINE_TAG(str, bdo, __VA_ARGS__)
	#endif
	#ifndef $$blockquote
		#define $$blockquote(str, ...) INLINE_TAG(str, blockquote, __VA_ARGS__)
	#endif
	#ifndef $$body
		#define $$body(str, ...) INLINE_TAG(str, body, __VA_ARGS__)
	#endif
	#ifndef $$br
		#define $$br(str, ...) INLINE_TAG(str, br, __VA_ARGS__)
	#endif
	#ifndef $$button
		#define $$button(str, ...) INLINE_TAG(str, button, __VA_ARGS__)
	#endif
	#ifndef $$canvas
		#define $$canvas(str, ...) INLINE_TAG(str, canvas, __VA_ARGS__)
	#endif
	#ifndef $$caption
		#define $$caption(str, ...) INLINE_TAG(str, caption, __VA_ARGS__)
	#endif
	#ifndef $$cite
		#define $$cite(str, ...) INLINE_TAG(str, cite, __VA_ARGS__)
	#endif
	#ifndef $$code
		#define $$code(str, ...) INLINE_TAG(str, code, __VA_ARGS__)
	#endif
	#ifndef $$col
		#define $$col(str, ...) INLINE_TAG(str, col, __VA_ARGS__)
	#endif
	#ifndef $$colgroup
		#define $$colgroup(str, ...) INLINE_TAG(str, colgroup, __VA_ARGS__)
	#endif
	#ifndef $$command
		#define $$command(str, ...) INLINE_TAG(str, command, __VA_ARGS__)
	#endif
	#ifndef $$datagrid
		#define $$datagrid(str, ...) INLINE_TAG(str, datagrid, __VA_ARGS__)
	#endif
	#ifndef $$datalist
		#define $$datalist(str, ...) INLINE_TAG(str, datalist, __VA_ARGS__)
	#endif
	#ifndef $$dd
		#define $$dd(str, ...) INLINE_TAG(str, dd, __VA_ARGS__)
	#endif
	#ifndef $$del
		#define $$del(str, ...) INLINE_TAG(str, del, __VA_ARGS__)
	#endif
	#ifndef $$details
		#define $$details(str, ...) INLINE_TAG(str, details, __VA_ARGS__)
	#endif
	#ifndef $$dfn
		#define $$dfn(str, ...) INLINE_TAG(str, dfn, __VA_ARGS__)
	#endif
	#ifndef $$div
		#define $$div(str, ...) INLINE_TAG(str, div, __VA_ARGS__)
	#endif
	#ifndef $$dl
		#define $$dl(str, ...) INLINE_TAG(str, dl, __VA_ARGS__)
	#endif
	#ifndef $$dt
		#define $$dt(str, ...) INLINE_TAG(str, dt, __VA_ARGS__)
	#endif
	#ifndef $$em
		#define $$em(str, ...) INLINE_TAG(str, em, __VA_ARGS__)
	#endif
	#ifndef $$embed
		#define $$embed(str, ...) INLINE_TAG(str, embed, __VA_ARGS__)
	#endif
	#ifndef $$eventsource
		#define $$eventsource(str, ...) INLINE_TAG(str, eventsource, __VA_ARGS__)
	#endif
	#ifndef $$fieldset
		#define $$fieldset(str, ...) INLINE_TAG(str, fieldset, __VA_ARGS__)
	#endif
	#ifndef $$figcaption
		#define $$figcaption(str, ...) INLINE_TAG(str, figcaption, __VA_ARGS__)
	#endif
	#ifndef $$figure
		#define $$figure(str, ...) INLINE_TAG(str, figure, __VA_ARGS__)
	#endif
	#ifndef $$footer
		#define $$footer(str, ...) INLINE_TAG(str, footer, __VA_ARGS__)
	#endif
	#ifndef $$form
		#define $$form(str, ...) INLINE_TAG(str, form, __VA_ARGS__)
	#endif
	#ifndef $$h1
		#define $$h1(str, ...) INLINE_TAG(str, h1, __VA_ARGS__)
	#endif
	#ifndef $$h2
		#define $$h2(str, ...) INLINE_TAG(str, h2, __VA_ARGS__)
	#endif
	#ifndef $$h3
		#define $$h3(str, ...) INLINE_TAG(str, h3, __VA_ARGS__)
	#endif
	#ifndef $$h4
		#define $$h4(str, ...) INLINE_TAG(str, h4, __VA_ARGS__)
	#endif
	#ifndef $$h5
		#define $$h5(str, ...) INLINE_TAG(str, h5, __VA_ARGS__)
	#endif
	#ifndef $$h6
		#define $$h6(str, ...) INLINE_TAG(str, h6, __VA_ARGS__)
	#endif
	#ifndef $$head
		#define $$head(str, ...) INLINE_TAG(str, head, __VA_ARGS__)
	#endif
	#ifndef $$header
		#define $$header(str, ...) INLINE_TAG(str, header, __VA_ARGS__)
	#endif
	#ifndef $$hgroup
		#define $$hgroup(str, ...) INLINE_TAG(str, hgroup, __VA_ARGS__)
	#endif
	#ifndef $$hr
		#define $$hr(str, ...) INLINE_TAG(str, hr, __VA_ARGS__)
	#endif
	#ifndef $$html
		#define $$html(str, ...) INLINE_TAG(str, html, __VA_ARGS__)
	#endif
	#ifndef $$i
		#define $$i(str, ...) INLINE_TAG(str, i, __VA_ARGS__)
	#endif
	#ifndef $$iframe
		#define $$iframe(str, ...) INLINE_TAG(str, iframe, __VA_ARGS__)
	#endif
	#ifndef $$img
		#define $$img(str, ...) INLINE_TAG(str, img, __VA_ARGS__)
	#endif
	#ifndef $$input
		#define $$input(str, ...) INLINE_TAG(str, input, __VA_ARGS__)
	#endif
	#ifndef $$ins
		#define $$ins(str, ...) INLINE_TAG(str, ins, __VA_ARGS__)
	#endif
	#ifndef $$kbd
		#define $$kbd(str, ...) INLINE_TAG(str, kbd, __VA_ARGS__)
	#endif
	#ifndef $$keygen
		#define $$keygen(str, ...) INLINE_TAG(str, keygen, __VA_ARGS__)
	#endif
	#ifndef $$label
		#define $$label(str, ...) INLINE_TAG(str, label, __VA_ARGS__)
	#endif
	#ifndef $$legend
		#define $$legend(str, ...) INLINE_TAG(str, legend, __VA_ARGS__)
	#endif
	#ifndef $$li
		#define $$li(str, ...) INLINE_TAG(str, li, __VA_ARGS__)
	#endif
	#ifndef $$link
		#define $$link(str, ...) INLINE_TAG(str, link, __VA_ARGS__)
	#endif
	#ifndef $$mark
		#define $$mark(str, ...) INLINE_TAG(str, mark, __VA_ARGS__)
	#endif
	#ifndef $$map
		#define $$map(str, ...) INLINE_TAG(str, map, __VA_ARGS__)
	#endif
	#ifndef $$menu
		#define $$menu(str, ...) INLINE_TAG(str, menu, __VA_ARGS__)
	#endif
	#ifndef $$meta
		#define $$meta(str, ...) INLINE_TAG(str, meta, __VA_ARGS__)
	#endif
	#ifndef $$meter
		#define $$meter(str, ...) INLINE_TAG(str, meter, __VA_ARGS__)
	#endif
	#ifndef $$nav
		#define $$nav(str, ...) INLINE_TAG(str, nav, __VA_ARGS__)
	#endif
	#ifndef $$noscript
		#define $$noscript(str, ...) INLINE_TAG(str, noscript, __VA_ARGS__)
	#endif
	#ifndef $$object
		#define $$object(str, ...) INLINE_TAG(str, object, __VA_ARGS__)
	#endif
	#ifndef $$ol
		#define $$ol(str, ...) INLINE_TAG(str, ol, __VA_ARGS__)
	#endif
	#ifndef $$optgroup
		#define $$optgroup(str, ...) INLINE_TAG(str, optgroup, __VA_ARGS__)
	#endif
	#ifndef $$option
		#define $$option(str, ...) INLINE_TAG(str, option, __VA_ARGS__)
	#endif
	#ifndef $$output
		#define $$output(str, ...) INLINE_TAG(str, output, __VA_ARGS__)
	#endif
	#ifndef $$p
		#define $$p(str, ...) INLINE_TAG(str, p, __VA_ARGS__)
	#endif
	#ifndef $$param
		#define $$param(str, ...) INLINE_TAG(str, param, __VA_ARGS__)
	#endif
	#ifndef $$pre
		#define $$pre(str, ...) INLINE_TAG(str, pre, __VA_ARGS__)
	#endif
	#ifndef $$progress
		#define $$progress(str, ...) INLINE_TAG(str, progress, __VA_ARGS__)
	#endif
	#ifndef $$q
		#define $$q(str, ...) INLINE_TAG(str, q, __VA_ARGS__)
	#endif
	#ifndef $$ruby
		#define $$ruby(str, ...) INLINE_TAG(str, ruby, __VA_ARGS__)
	#endif
	#ifndef $$rp
		#define $$rp(str, ...) INLINE_TAG(str, rp, __VA_ARGS__)
	#endif
	#ifndef $$rt
		#define $$rt(str, ...) INLINE_TAG(str, rt, __VA_ARGS__)
	#endif
	#ifndef $$samp
		#define $$samp(str, ...) INLINE_TAG(str, samp, __VA_ARGS__)
	#endif
	#ifndef $$script
		#define $$script(str, ...) INLINE_TAG(str, script, __VA_ARGS__)
	#endif
	#ifndef $$section
		#define $$section(str, ...) INLINE_TAG(str, section, __VA_ARGS__)
	#endif
	#ifndef $$select
		#define $$select(str, ...) INLINE_TAG(str, select, __VA_ARGS__)
	#endif
	#ifndef $$small
		#define $$small(str, ...) INLINE_TAG(str, small, __VA_ARGS__)
	#endif
	#ifndef $$source
		#define $$source(str, ...) INLINE_TAG(str, source, __VA_ARGS__)
	#endif
	#ifndef $$span
		#define $$span(str, ...) INLINE_TAG(str, span, __VA_ARGS__)
	#endif
	#ifndef $$strong
		#define $$strong(str, ...) INLINE_TAG(str, strong, __VA_ARGS__)
	#endif
	#ifndef $$style
		#define $$style(str, ...) INLINE_TAG(str, style, __VA_ARGS__)
	#endif
	#ifndef $$sub
		#define $$sub(str, ...) INLINE_TAG(str, sub, __VA_ARGS__)
	#endif
	#ifndef $$summary
		#define $$summary(str, ...) INLINE_TAG(str, summary, __VA_ARGS__)
	#endif
	#ifndef $$sup
		#define $$sup(str, ...) INLINE_TAG(str, sup, __VA_ARGS__)
	#endif
	#ifndef $$table
		#define $$table(str, ...) INLINE_TAG(str, table, __VA_ARGS__)
	#endif
	#ifndef $$tbody
		#define $$tbody(str, ...) INLINE_TAG(str, tbody, __VA_ARGS__)
	#endif
	#ifndef $$td
		#define $$td(str, ...) INLINE_TAG(str, td, __VA_ARGS__)
	#endif
	#ifndef $$textarea
		#define $$textarea(str, ...) INLINE_TAG(str, textarea, __VA_ARGS__)
	#endif
	#ifndef $$tfoot
		#define $$tfoot(str, ...) INLINE_TAG(str, tfoot, __VA_ARGS__)
	#endif
	#ifndef $$th
		#define $$th(str, ...) INLINE_TAG(str, th, __VA_ARGS__)
	#endif
	#ifndef $$thead
		#define $$thead(str, ...) INLINE_TAG(str, thead, __VA_ARGS__)
	#endif
	#ifndef $$time
		#define $$time(str, ...) INLINE_TAG(str, time, __VA_ARGS__)
	#endif
	#ifndef $$title
		#define $$title(str, ...) INLINE_TAG(str, title, __VA_ARGS__)
	#endif
	#ifndef $$tr
		#define $$tr(str, ...) INLINE_TAG(str, tr, __VA_ARGS__)
	#endif
	#ifndef $$ul
		#define $$ul(str, ...) INLINE_TAG(str, ul, __VA_ARGS__)
	#endif
	#ifndef $$var
		#define $$var(str, ...) INLINE_TAG(str, var, __VA_ARGS__)
	#endif
	#ifndef $$video
		#define $$video(str, ...) INLINE_TAG(str, video, __VA_ARGS__)
	#endif
	#ifndef $$wbr
		#define $$wbr(str, ...) INLINE_TAG(str, wbr, __VA_ARGS__)
	#endif
#endif

//XHTML-style self-closing tags with arguments. Convention: xtagname(...)
#if true
	#ifndef xa
		#define xa(...) HTTP_X_TAG(a, __VA_ARGS__)
	#endif
	#ifndef xabbr
		#define xabbr(...) HTTP_X_TAG(abbr, __VA_ARGS__)
	#endif
	#ifndef xaddress
		#define xaddress(...) HTTP_X_TAG(address, __VA_ARGS__)
	#endif
	#ifndef xarea
		#define xarea(...) HTTP_X_TAG(area, __VA_ARGS__)
	#endif
	#ifndef xarticle
		#define xarticle(...) HTTP_X_TAG(article, __VA_ARGS__)
	#endif
	#ifndef xaside
		#define xaside(...) HTTP_X_TAG(aside, __VA_ARGS__)
	#endif
	#ifndef xaudio
		#define xaudio(...) HTTP_X_TAG(audio, __VA_ARGS__)
	#endif
	#ifndef xb
		#define xb(...) HTTP_X_TAG(b, __VA_ARGS__)
	#endif
	#ifndef xbase
		#define xbase(...) HTTP_X_TAG(base, __VA_ARGS__)
	#endif
	#ifndef xbb
		#define xbb(...) HTTP_X_TAG(bb, __VA_ARGS__)
	#endif
	#ifndef xbdo
		#define xbdo(...) HTTP_X_TAG(bdo, __VA_ARGS__)
	#endif
	#ifndef xblockquote
		#define xblockquote(...) HTTP_X_TAG(blockquote, __VA_ARGS__)
	#endif
	#ifndef xbody
		#define xbody(...) HTTP_X_TAG(body, __VA_ARGS__)
	#endif
	#ifndef xbr
		#define xbr(...) HTTP_X_TAG(br, __VA_ARGS__)
	#endif
	#ifndef xbutton
		#define xbutton(...) HTTP_X_TAG(button, __VA_ARGS__)
	#endif
	#ifndef xcanvas
		#define xcanvas(...) HTTP_X_TAG(canvas, __VA_ARGS__)
	#endif
	#ifndef xcaption
		#define xcaption(...) HTTP_X_TAG(caption, __VA_ARGS__)
	#endif
	#ifndef xcite
		#define xcite(...) HTTP_X_TAG(cite, __VA_ARGS__)
	#endif
	#ifndef xcode
		#define xcode(...) HTTP_X_TAG(code, __VA_ARGS__)
	#endif
	#ifndef xcol
		#define xcol(...) HTTP_X_TAG(col, __VA_ARGS__)
	#endif
	#ifndef xcolgroup
		#define xcolgroup(...) HTTP_X_TAG(colgroup, __VA_ARGS__)
	#endif
	#ifndef xcommand
		#define xcommand(...) HTTP_X_TAG(command, __VA_ARGS__)
	#endif
	#ifndef xdatagrid
		#define xdatagrid(...) HTTP_X_TAG(datagrid, __VA_ARGS__)
	#endif
	#ifndef xdatalist
		#define xdatalist(...) HTTP_X_TAG(datalist, __VA_ARGS__)
	#endif
	#ifndef xdd
		#define xdd(...) HTTP_X_TAG(dd, __VA_ARGS__)
	#endif
	#ifndef xdel
		#define xdel(...) HTTP_X_TAG(del, __VA_ARGS__)
	#endif
	#ifndef xdetails
		#define xdetails(...) HTTP_X_TAG(details, __VA_ARGS__)
	#endif
	#ifndef xdfn
		#define xdfn(...) HTTP_X_TAG(dfn, __VA_ARGS__)
	#endif
	#ifndef xdiv
		#define xdiv(...) HTTP_X_TAG(div, __VA_ARGS__)
	#endif
	#ifndef xdl
		#define xdl(...) HTTP_X_TAG(dl, __VA_ARGS__)
	#endif
	#ifndef xdt
		#define xdt(...) HTTP_X_TAG(dt, __VA_ARGS__)
	#endif
	#ifndef xem
		#define xem(...) HTTP_X_TAG(em, __VA_ARGS__)
	#endif
	#ifndef xembed
		#define xembed(...) HTTP_X_TAG(embed, __VA_ARGS__)
	#endif
	#ifndef xeventsource
		#define xeventsource(...) HTTP_X_TAG(eventsource, __VA_ARGS__)
	#endif
	#ifndef xfieldset
		#define xfieldset(...) HTTP_X_TAG(fieldset, __VA_ARGS__)
	#endif
	#ifndef xfigcaption
		#define xfigcaption(...) HTTP_X_TAG(figcaption, __VA_ARGS__)
	#endif
	#ifndef xfigure
		#define xfigure(...) HTTP_X_TAG(figure, __VA_ARGS__)
	#endif
	#ifndef xfooter
		#define xfooter(...) HTTP_X_TAG(footer, __VA_ARGS__)
	#endif
	#ifndef xform
		#define xform(...) HTTP_X_TAG(form, __VA_ARGS__)
	#endif
	#ifndef xh1
		#define xh1(...) HTTP_X_TAG(h1, __VA_ARGS__)
	#endif
	#ifndef xh2
		#define xh2(...) HTTP_X_TAG(h2, __VA_ARGS__)
	#endif
	#ifndef xh3
		#define xh3(...) HTTP_X_TAG(h3, __VA_ARGS__)
	#endif
	#ifndef xh4
		#define xh4(...) HTTP_X_TAG(h4, __VA_ARGS__)
	#endif
	#ifndef xh5
		#define xh5(...) HTTP_X_TAG(h5, __VA_ARGS__)
	#endif
	#ifndef xh6
		#define xh6(...) HTTP_X_TAG(h6, __VA_ARGS__)
	#endif
	#ifndef xhead
		#define xhead(...) HTTP_X_TAG(head, __VA_ARGS__)
	#endif
	#ifndef xheader
		#define xheader(...) HTTP_X_TAG(header, __VA_ARGS__)
	#endif
	#ifndef xhgroup
		#define xhgroup(...) HTTP_X_TAG(hgroup, __VA_ARGS__)
	#endif
	#ifndef xhr
		#define xhr(...) HTTP_X_TAG(hr, __VA_ARGS__)
	#endif
	#ifndef xhtml
		#define xhtml(...) HTTP_X_TAG(html, __VA_ARGS__)
	#endif
	#ifndef xi
		#define xi(...) HTTP_X_TAG(i, __VA_ARGS__)
	#endif
	#ifndef xiframe
		#define xiframe(...) HTTP_X_TAG(iframe, __VA_ARGS__)
	#endif
	#ifndef ximg
		#define ximg(...) HTTP_X_TAG(img, __VA_ARGS__)
	#endif
	#ifndef xinput
		#define xinput(...) HTTP_X_TAG(input, __VA_ARGS__)
	#endif
	#ifndef xins
		#define xins(...) HTTP_X_TAG(ins, __VA_ARGS__)
	#endif
	#ifndef xkbd
		#define xkbd(...) HTTP_X_TAG(kbd, __VA_ARGS__)
	#endif
	#ifndef xkeygen
		#define xkeygen(...) HTTP_X_TAG(keygen, __VA_ARGS__)
	#endif
	#ifndef xlabel
		#define xlabel(...) HTTP_X_TAG(label, __VA_ARGS__)
	#endif
	#ifndef xlegend
		#define xlegend(...) HTTP_X_TAG(legend, __VA_ARGS__)
	#endif
	#ifndef xli
		#define xli(...) HTTP_X_TAG(li, __VA_ARGS__)
	#endif
	#ifndef xlink
		#define xlink(...) HTTP_X_TAG(link, __VA_ARGS__)
	#endif
	#ifndef xmark
		#define xmark(...) HTTP_X_TAG(mark, __VA_ARGS__)
	#endif
	#ifndef xmap
		#define xmap(...) HTTP_X_TAG(map, __VA_ARGS__)
	#endif
	#ifndef xmenu
		#define xmenu(...) HTTP_X_TAG(menu, __VA_ARGS__)
	#endif
	#ifndef xmeta
		#define xmeta(...) HTTP_X_TAG(meta, __VA_ARGS__)
	#endif
	#ifndef xmeter
		#define xmeter(...) HTTP_X_TAG(meter, __VA_ARGS__)
	#endif
	#ifndef xnav
		#define xnav(...) HTTP_X_TAG(nav, __VA_ARGS__)
	#endif
	#ifndef xnoscript
		#define xnoscript(...) HTTP_X_TAG(noscript, __VA_ARGS__)
	#endif
	#ifndef xobject
		#define xobject(...) HTTP_X_TAG(object, __VA_ARGS__)
	#endif
	#ifndef xol
		#define xol(...) HTTP_X_TAG(ol, __VA_ARGS__)
	#endif
	#ifndef xoptgroup
		#define xoptgroup(...) HTTP_X_TAG(optgroup, __VA_ARGS__)
	#endif
	#ifndef xoption
		#define xoption(...) HTTP_X_TAG(option, __VA_ARGS__)
	#endif
	#ifndef xoutput
		#define xoutput(...) HTTP_X_TAG(output, __VA_ARGS__)
	#endif
	#ifndef xp
		#define xp(...) HTTP_X_TAG(p, __VA_ARGS__)
	#endif
	#ifndef xparam
		#define xparam(...) HTTP_X_TAG(param, __VA_ARGS__)
	#endif
	#ifndef xpre
		#define xpre(...) HTTP_X_TAG(pre, __VA_ARGS__)
	#endif
	#ifndef xprogress
		#define xprogress(...) HTTP_X_TAG(progress, __VA_ARGS__)
	#endif
	#ifndef xq
		#define xq(...) HTTP_X_TAG(q, __VA_ARGS__)
	#endif
	#ifndef xruby
		#define xruby(...) HTTP_X_TAG(ruby, __VA_ARGS__)
	#endif
	#ifndef xrp
		#define xrp(...) HTTP_X_TAG(rp, __VA_ARGS__)
	#endif
	#ifndef xrt
		#define xrt(...) HTTP_X_TAG(rt, __VA_ARGS__)
	#endif
	#ifndef xsamp
		#define xsamp(...) HTTP_X_TAG(samp, __VA_ARGS__)
	#endif
	#ifndef xscript
		#define xscript(...) HTTP_X_TAG(script, __VA_ARGS__)
	#endif
	#ifndef xsection
		#define xsection(...) HTTP_X_TAG(section, __VA_ARGS__)
	#endif
	#ifndef xselect
		#define xselect(...) HTTP_X_TAG(select, __VA_ARGS__)
	#endif
	#ifndef xsmall
		#define xsmall(...) HTTP_X_TAG(small, __VA_ARGS__)
	#endif
	#ifndef xsource
		#define xsource(...) HTTP_X_TAG(source, __VA_ARGS__)
	#endif
	#ifndef xspan
		#define xspan(...) HTTP_X_TAG(span, __VA_ARGS__)
	#endif
	#ifndef xstrong
		#define xstrong(...) HTTP_X_TAG(strong, __VA_ARGS__)
	#endif
	#ifndef xstyle
		#define xstyle(...) HTTP_X_TAG(style, __VA_ARGS__)
	#endif
	#ifndef xsub
		#define xsub(...) HTTP_X_TAG(sub, __VA_ARGS__)
	#endif
	#ifndef xsummary
		#define xsummary(...) HTTP_X_TAG(summary, __VA_ARGS__)
	#endif
	#ifndef xsup
		#define xsup(...) HTTP_X_TAG(sup, __VA_ARGS__)
	#endif
	#ifndef xtable
		#define xtable(...) HTTP_X_TAG(table, __VA_ARGS__)
	#endif
	#ifndef xtbody
		#define xtbody(...) HTTP_X_TAG(tbody, __VA_ARGS__)
	#endif
	#ifndef xtd
		#define xtd(...) HTTP_X_TAG(td, __VA_ARGS__)
	#endif
	#ifndef xtextarea
		#define xtextarea(...) HTTP_X_TAG(textarea, __VA_ARGS__)
	#endif
	#ifndef xtfoot
		#define xtfoot(...) HTTP_X_TAG(tfoot, __VA_ARGS__)
	#endif
	#ifndef xth
		#define xth(...) HTTP_X_TAG(th, __VA_ARGS__)
	#endif
	#ifndef xthead
		#define xthead(...) HTTP_X_TAG(thead, __VA_ARGS__)
	#endif
	#ifndef xtime
		#define xtime(...) HTTP_X_TAG(time, __VA_ARGS__)
	#endif
	#ifndef xtitle
		#define xtitle(...) HTTP_X_TAG(title, __VA_ARGS__)
	#endif
	#ifndef xtr
		#define xtr(...) HTTP_X_TAG(tr, __VA_ARGS__)
	#endif
	#ifndef xul
		#define xul(...) HTTP_X_TAG(ul, __VA_ARGS__)
	#endif
	#ifndef xvar
		#define xvar(...) HTTP_X_TAG(var, __VA_ARGS__)
	#endif
	#ifndef xvideo
		#define xvideo(...) HTTP_X_TAG(video, __VA_ARGS__)
	#endif
	#ifndef xwbr
		#define xwbr(...) HTTP_X_TAG(wbr, __VA_ARGS__)
	#endif
#endif

//XHTML-style self-closing tags with no arguments. Convention: xTAGNAME
#if true
	#ifndef xA
		#define xA xa()
	#endif
	#ifndef xABBR
		#define xABBR xabbr()
	#endif
	#ifndef xADDRESS
		#define xADDRESS xaddress()
	#endif
	#ifndef xAREA
		#define xAREA xarea()
	#endif
	#ifndef xARTICLE
		#define xARTICLE xarticle()
	#endif
	#ifndef xASIDE
		#define xASIDE xaside()
	#endif
	#ifndef xAUDIO
		#define xAUDIO xaudio()
	#endif
	#ifndef xB
		#define xB xb()
	#endif
	#ifndef xBASE
		#define xBASE xbase()
	#endif
	#ifndef xBB
		#define xBB xbb()
	#endif
	#ifndef xBDO
		#define xBDO xbdo()
	#endif
	#ifndef xBLOCKQUOTE
		#define xBLOCKQUOTE xblockquote()
	#endif
	#ifndef xBODY
		#define xBODY xbody()
	#endif
	#ifndef xBR
		#define xBR xbr()
	#endif
	#ifndef xBUTTON
		#define xBUTTON xbutton()
	#endif
	#ifndef xCANVAS
		#define xCANVAS xcanvas()
	#endif
	#ifndef xCAPTION
		#define xCAPTION xcaption()
	#endif
	#ifndef xCITE
		#define xCITE xcite()
	#endif
	#ifndef xCODE
		#define xCODE xcode()
	#endif
	#ifndef xCOL
		#define xCOL xcol()
	#endif
	#ifndef xCOLGROUP
		#define xCOLGROUP xcolgroup()
	#endif
	#ifndef xCOMMAND
		#define xCOMMAND xcommand()
	#endif
	#ifndef xDATAGRID
		#define xDATAGRID xdatagrid()
	#endif
	#ifndef xDATALIST
		#define xDATALIST xdatalist()
	#endif
	#ifndef xDD
		#define xDD xdd()
	#endif
	#ifndef xDEL
		#define xDEL xdel()
	#endif
	#ifndef xDETAILS
		#define xDETAILS xdetails()
	#endif
	#ifndef xDFN
		#define xDFN xdfn()
	#endif
	#ifndef xDIV
		#define xDIV xdiv()
	#endif
	#ifndef xDL
		#define xDL xdl()
	#endif
	#ifndef xDT
		#define xDT xdt()
	#endif
	#ifndef xEM
		#define xEM xem()
	#endif
	#ifndef xEMBED
		#define xEMBED xembed()
	#endif
	#ifndef xEVENTSOURCE
		#define xEVENTSOURCE xeventsource()
	#endif
	#ifndef xFIELDSET
		#define xFIELDSET xfieldset()
	#endif
	#ifndef xFIGCAPTION
		#define xFIGCAPTION xfigcaption()
	#endif
	#ifndef xFIGURE
		#define xFIGURE xfigure()
	#endif
	#ifndef xFOOTER
		#define xFOOTER xfooter()
	#endif
	#ifndef xFORM
		#define xFORM xform()
	#endif
	#ifndef xH1
		#define xH1 xh1()
	#endif
	#ifndef xH2
		#define xH2 xh2()
	#endif
	#ifndef xH3
		#define xH3 xh3()
	#endif
	#ifndef xH4
		#define xH4 xh4()
	#endif
	#ifndef xH5
		#define xH5 xh5()
	#endif
	#ifndef xH6
		#define xH6 xh6()
	#endif
	#ifndef xHEAD
		#define xHEAD xhead()
	#endif
	#ifndef xHEADER
		#define xHEADER xheader()
	#endif
	#ifndef xHGROUP
		#define xHGROUP xhgroup()
	#endif
	#ifndef xHR
		#define xHR xhr()
	#endif
	#ifndef xHTML
		#define xHTML xhtml()
	#endif
	#ifndef xI
		#define xI xi()
	#endif
	#ifndef xIFRAME
		#define xIFRAME xiframe()
	#endif
	#ifndef xIMG
		#define xIMG ximg()
	#endif
	#ifndef xINPUT
		#define xINPUT xinput()
	#endif
	#ifndef xINS
		#define xINS xins()
	#endif
	#ifndef xKBD
		#define xKBD xkbd()
	#endif
	#ifndef xKEYGEN
		#define xKEYGEN xkeygen()
	#endif
	#ifndef xLABEL
		#define xLABEL xlabel()
	#endif
	#ifndef xLEGEND
		#define xLEGEND xlegend()
	#endif
	#ifndef xLI
		#define xLI xli()
	#endif
	#ifndef xLINK
		#define xLINK xlink()
	#endif
	#ifndef xMARK
		#define xMARK xmark()
	#endif
	#ifndef xMAP
		#define xMAP xmap()
	#endif
	#ifndef xMENU
		#define xMENU xmenu()
	#endif
	#ifndef xMETA
		#define xMETA xmeta()
	#endif
	#ifndef xMETER
		#define xMETER xmeter()
	#endif
	#ifndef xNAV
		#define xNAV xnav()
	#endif
	#ifndef xNOSCRIPT
		#define xNOSCRIPT xnoscript()
	#endif
	#ifndef xOBJECT
		#define xOBJECT xobject()
	#endif
	#ifndef xOL
		#define xOL xol()
	#endif
	#ifndef xOPTGROUP
		#define xOPTGROUP xoptgroup()
	#endif
	#ifndef xOPTION
		#define xOPTION xoption()
	#endif
	#ifndef xOUTPUT
		#define xOUTPUT xoutput()
	#endif
	#ifndef xP
		#define xP xp()
	#endif
	#ifndef xPARAM
		#define xPARAM xparam()
	#endif
	#ifndef xPRE
		#define xPRE xpre()
	#endif
	#ifndef xPROGRESS
		#define xPROGRESS xprogress()
	#endif
	#ifndef xQ
		#define xQ xq()
	#endif
	#ifndef xRUBY
		#define xRUBY xruby()
	#endif
	#ifndef xRP
		#define xRP xrp()
	#endif
	#ifndef xRT
		#define xRT xrt()
	#endif
	#ifndef xSAMP
		#define xSAMP xsamp()
	#endif
	#ifndef xSCRIPT
		#define xSCRIPT xscript()
	#endif
	#ifndef xSECTION
		#define xSECTION xsection()
	#endif
	#ifndef xSELECT
		#define xSELECT xselect()
	#endif
	#ifndef xSMALL
		#define xSMALL xsmall()
	#endif
	#ifndef xSOURCE
		#define xSOURCE xsource()
	#endif
	#ifndef xSPAN
		#define xSPAN xspan()
	#endif
	#ifndef xSTRONG
		#define xSTRONG xstrong()
	#endif
	#ifndef xSTYLE
		#define xSTYLE xstyle()
	#endif
	#ifndef xSUB
		#define xSUB xsub()
	#endif
	#ifndef xSUMMARY
		#define xSUMMARY xsummary()
	#endif
	#ifndef xSUP
		#define xSUP xsup()
	#endif
	#ifndef xTABLE
		#define xTABLE xtable()
	#endif
	#ifndef xTBODY
		#define xTBODY xtbody()
	#endif
	#ifndef xTD
		#define xTD xtd()
	#endif
	#ifndef xTEXTAREA
		#define xTEXTAREA xtextarea()
	#endif
	#ifndef xTFOOT
		#define xTFOOT xtfoot()
	#endif
	#ifndef xTH
		#define xTH xth()
	#endif
	#ifndef xTHEAD
		#define xTHEAD xthead()
	#endif
	#ifndef xTIME
		#define xTIME xtime()
	#endif
	#ifndef xTITLE
		#define xTITLE xtitle()
	#endif
	#ifndef xTR
		#define xTR xtr()
	#endif
	#ifndef xUL
		#define xUL xul()
	#endif
	#ifndef xVAR
		#define xVAR xvar()
	#endif
	#ifndef xVIDEO
		#define xVIDEO xvideo()
	#endif
	#ifndef xWBR
		#define xWBR xwbr()
	#endif
#endif
