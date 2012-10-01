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

#endif
