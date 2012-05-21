/*************************
 *         htt++         *
 *************************
 *      Main Module      *
 *      Header File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#ifndef HTTPP_HPP_
#define HTTPP_HPP_

#include "JFormat.hpp"
#include "JHash.hpp"
#include "page.hpp"
#include "section.hpp"
#include "TagStructs.hpp"
#include "tags.hpp"
#include "mimetypes.hpp"
#include <fstream>

#define BIND(page) httpp::bind(#page, page)

namespace httpp
{
#ifdef THREADED
	void bind(std::string key, PageFunc page);
#else
	void bind(std::string key, BasePage &page, std::string ContentType = "");
	void regex_bind(std::string key, BasePage &page, std::string ContentType = "");
#endif

	DeclarePage(Basic404);
	DeclarePage(Basic400);
	DeclarePage(Static);

	void listen(int port);
}

#endif /* HTTPP_HPP_ */
