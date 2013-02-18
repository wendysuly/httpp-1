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

#define BIND(page) bind(#page, page)

namespace httpp
{

	DeclarePage(Basic404);
	DeclarePage(Basic400);
	DeclarePage(Static);

	class httpp_server
	{
	public:
		httpp_server() : BindMap(&PageMap::getName, false) {}
		void bind(const std::string &key, BasePage &page, const std::string &ContentType = "");
		void regex_bind(const std::string &key, BasePage &page, const std::string &ContentType = "");

		BasePage &GetPageRef(const std::string &location);
		BasePage *GetPage(const std::string &location);

		void listen(int port);
	private:
		JNet::ServerSocket Sock;
		//When possible, we'll use a map to find our pages.
		JHash::map<PageMap> BindMap;
		//Unfortunately, we can't do that with regular expressions.
		//We have to put regular expressions into a vector and step through it.
		//But at least we can minimize the size of the vector by keeping statically-named pages in the map.
		std::vector<PageMap> RegexMap;

		PageMap *Regex_GetPage(const std::string &location);
		PageMap *GetPageMap(const std::string &location);
		const static std::string ServerIdentStr;
		friend class Pages::page_Basic404;
		friend class Pages::page_Basic400;
	};
}

#endif /* HTTPP_HPP_ */
