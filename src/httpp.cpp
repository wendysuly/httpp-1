/*************************
 *         htt++         *
 *************************
 *      Main Module      *
 *      Source File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#include "jnet/JNet.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <boost/regex.hpp>
#include <thread>
#include "request.hpp"
#include "httpp.hpp"

namespace httpp
{
	JNet::ServerSocket Sock;
	//When possible, we'll use a map to find our pages.
	JHash::map<PageMap> BindMap(&PageMap::getName, false);
	//Unfortunately, we can't do that with regular expressions.
	//We have to put regular expressions into a vector and step through it.
	//But at least we can minimize the size of the vector by keeping statically-named pages in the map.
	std::vector<PageMap*> RegexMap;

	void bind(std::string key, BasePage &page, std::string ContentType)
	{
		PageMap *m = new PageMap("/"+key, page, ContentType);
		BindMap.push(m);
	}

	void regex_bind(std::string key, BasePage &page, std::string ContentType)
	{
		PageMap *m = new PageMap("/"+key, page, ContentType);
		RegexMap.push_back(m);
	}

	std::string ServerIdentStr = "htt++ Version 0.1 alpha. http://www.example.com/httpp/";

#include "html_start.hpp"
	DefinePage(Basic404)
	{
		HTML
		{
			HEAD
			{
				$title("Error 404: File Not Found");
			}
			BODY
			{
				$strong("Error 404: File Not Found");
				xBR;
				xBR;
				$i(ServerIdentStr);
			}
		}
	};

	DefinePage(Basic400)
	{
		HTML
		{
			HEAD
			{
				$title(JFormat::format("Error 400: {0}", getMessage()));
			}
			BODY
			{
				$strong(JFormat::format("Error 400: {0}", getMessage()));
				xBR;
				xBR;
				$i(ServerIdentStr);
			}
		}
	};

	DefinePage(Static)
	{
		static std::string str;
		static std::string ext;
		static std::string type;
		str = request.getPath();
		ext = "";
		std::ifstream f;
		f.open(str);
		if(f)
		{
			for(int i=str.length()-1;i>0;i--)
			{
				if(str[i] == '.')
					break;
				ext = str[i] + ext;
			}
			if((type = MimeTypes[ext]) == "")
			{
				type = "text/plain";
			}
			setHeader("Content-Type", type);
			$NN(f.rdbuf());
			f.close();
		}
		else
		{
			std::cout << "Could not open requested file " << str << std::endl;
			setStatus(httpStatus::rNOT_FOUND);
			Import(httpp::Basic404);
			f.close();
		}
	}
#include "html_end.hpp"

	PageMap *Regex_GetPage(std::string location)
	{
		unsigned int size = RegexMap.size();
		for(unsigned int i=0;i<size;i++)
		{
			boost::regex pattern(RegexMap[i]->getName());
			if(boost::regex_match(location, pattern))
				return RegexMap[i];
		}
		return nullptr;
	}

	PageMap *GetPageMap(std::string location)
	{
		PageMap *page;
		page = BindMap[location];
		if(page == nullptr)
			page = Regex_GetPage(location);
		return page;
	}

	BasePage &GetPageRef(const std::string &location)
	{
		PageMap *pagemap = GetPageMap(location);
		if(pagemap != nullptr)
			return pagemap->getPage();
		else
		{
			std::cout << "No mapping exists for " << location << std::endl;
			pagemap = BindMap["/404"];
			BasePage &page = pagemap->getPage();
			page.setStatus(httpStatus::rNOT_FOUND);
			return page;
		}
	}

	BasePage *GetPage(const std::string &location)
	{
		return &GetPageRef(location);
	}

	void listen(int port)
	{
		if(BindMap["/400"] == nullptr)
			bind("400", Basic400);
		if(BindMap["/404"] == nullptr)
			bind("404", Basic404);
		PopulateMimeTypes();
		JNet::Connection *c;
		Sock.listen(port);
		std::cout << "htt++ listening on port " << port << std::endl;
		int pnum = 0;
		int numCPU = std::thread::hardware_concurrency();
		while(pnum < numCPU && fork())
		{
			pnum++;
		}
		std::cout << "New process spawned: " << pnum << std::endl;
		std::string str;
		std::string body;
		std::string header;
		std::string response;
		PageMap *pagemap;
		BasePage *page;
		while(true)
		{
			Sock.HandleIO();
			for(int i=0;i<Sock.GetNumConnections();i++)
			{
				c = Sock.GetConnection(i);
				if(c->DataReady())
				{
					page = nullptr;
					Request request;
					str = c->GetLine();
					try
					{
						request.create(str);
						while((str = c->GetLine()) != "")
						{
							request.addHeader(str);
						}
						if((str = c->GetLine()) != "")
							request.addRequestVars(str);
					}
					catch(HTTPException &e)
					{
						std::stringstream s;
						s << "/" << e.getCode();
						pagemap = BindMap[s.str()];
						page = &pagemap->getPage();
						page->setStatus((static_cast<httpStatus>(e.getCode())));
						page->setMessage(e.getMsg());
					}
					if(page == nullptr)
					{
						pagemap = GetPageMap(request.getLocation());
						page = &pagemap->getPage();
					}
					//operator()
					body = (*page)(&request);
					if(pagemap->getContentType() != "" && page->getStatus() == httpStatus::rOK)
						page->setHeader("Content-Type", pagemap->getContentType());
					header = page->getHeaders();
					response = header + body;
					//std::cout << std::endl << pnum << ": Sending response headers: " << page->getPage().getHeaders();
					c->SendNow(response);
					//Revert any status changes we've made to the page, so it returns OK next time.
					page->setStatus(httpStatus::rOK);
					if(request.getVersion() != "HTTP/1.1" && strToLower(request["Connection"]) != "keep-alive")
						Sock.CloseConnection(i);
				}
			}
		}
	}
}
