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

#include "jformat/JFormat.hpp"
#include "jhash/JHash.hpp"
#include "page.hpp"
#include "section.hpp"
#include "TagStructs.hpp"
#include "tags.hpp"
#include "mimetypes.hpp"
#include <fstream>
#include "request.hpp"

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

	BasePage &GetPageRef(const std::string &location);
	BasePage *GetPage(const std::string &location);

	void listen(int port);
}

#endif /* HTTPP_HPP_ */
