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
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <queue>
#include <sys/prctl.h>
#include <map>

namespace httpp
{

	void httpp_server::bind(const std::string &key, BasePage &page, const std::string &ContentType)
	{
		BindMap.push(PageMap("/"+key, page, ContentType));
	}

	void httpp_server::regex_bind(const std::string &key, BasePage &page, const std::string &ContentType)
	{
		RegexMap.push_back(PageMap("/"+key, page, ContentType));
	}

	const std::string httpp_server::ServerIdentStr = "htt++ Version 0.1 alpha. http://www.example.com/httpp/";

	std::queue<std::tuple<PageMap*, JNet::Connection*, Request*, int, std::string>> RequestQueue;
	std::queue<JNet::Connection*> CloseQueue;
	boost::mutex CloseMutex;
	boost::mutex RequestMutex;

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
				$i(httpp_server::ServerIdentStr);
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
				$i(httpp_server::ServerIdentStr);
			}
		}
	};

	DefinePage(Static)
	{
		std::string str;
		std::string ext;
		std::string type;
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
			if(MimeTypes.find(ext) != MimeTypes.end())
			{
				type = MimeTypes[ext].getMimeType();
			}
			else
			{
				type = "text/plain";
			}
			setHeader("Content-Type", type);
			$NN(f.rdbuf());
			f.close();
		}
		else
		{
			//std::cout << "Could not open requested file " << str << std::endl;
			setStatus(httpStatus::rNOT_FOUND);
			Import(httpp::Basic404);
			f.close();
		}
	}
#include "html_end.hpp"

	PageMap *httpp_server::Regex_GetPage(const std::string &location)
	{
		unsigned int size = RegexMap.size();
		for(unsigned int i=0;i<size;i++)
		{
			boost::regex pattern(RegexMap[i].getName());
			if(boost::regex_match(location, pattern))
				return &RegexMap[i];
		}
		return nullptr;
	}

	PageMap *httpp_server::GetPageMap(const std::string &location)
	{
		try
		{
			return &BindMap[location];
		}
		catch(JHash::no_such_element &e)
		{
			return Regex_GetPage(location);
		}
	}

	BasePage &httpp_server::GetPageRef(const std::string &location)
	{
		PageMap *pagemap = GetPageMap(location);
		if(pagemap != nullptr)
			return pagemap->getPage();
		else
		{
			pagemap = &BindMap["/404"];
			BasePage &page = pagemap->getPage();
			page.setStatus(httpStatus::rNOT_FOUND);
			return page;
		}
	}

	BasePage *httpp_server::GetPage(const std::string &location)
	{
		return &GetPageRef(location);
	}

	void worker()
	{
		prctl(PR_SET_NAME,"htt++-worker",0,0,0);
		std::map<BasePage*, BasePage*> Pages;
		std::string body;
		PageMap *pagemap;
		BasePage *page;
		BasePage *key;
		Request *request;
		std::string header;
		std::string response;
		JNet::Connection *c;
		int code;
		std::string msg;
		std::tuple<PageMap*, JNet::Connection*, Request*, int, std::string> rq;
		while(true)
		{
			RequestMutex.lock();
			if(RequestQueue.empty())
			{
				RequestMutex.unlock();
			}
			else
			{
				rq = RequestQueue.front();
				RequestQueue.pop();
				RequestMutex.unlock();
				pagemap = std::get<0>(rq);
				c = std::get<1>(rq);
				request = std::get<2>(rq);
				code = std::get<3>(rq);
				msg = std::get<4>(rq);
				//operator()
				key = &(pagemap->getPage());
				if(Pages.find(key) == Pages.end())
				{
					page = (pagemap->getPage().clone());
					Pages[key] = page;
				}
				else
				{
					page = Pages[key];
				}
				page->setStatus(static_cast<httpStatus>(code));
				if(msg != "")
				{
					page->setMessage(msg);
				}
				body = (*page)(request);
				if(pagemap->getContentType() != "" && page->getStatus() == httpStatus::rOK)
					page->setHeader("Content-Type", pagemap->getContentType());
				header = page->getHeaders();
				response = header + body;
				//std::cout << std::endl << "Sending response headers: " << page->getHeaders();
				c->Send(response);
				//Revert any status changes we've made to the page, so it returns OK next time.
				page->setStatus(httpStatus::rOK);
				if(request->getVersion() != "HTTP/1.1" && strToLower((*request)["Connection"]) != "keep-alive")
					CloseQueue.push(c);
				delete request;
			}
			usleep(10000);
		}
	}

	void httpp_server::listen(int port)
	{
		int i=0;
		prctl(PR_SET_NAME,"htt++-listener",0,0,0);
		if(BindMap.find("/400") == BindMap.end())
			bind("400", Basic400);
		if(BindMap.find("/404") == BindMap.end())
			bind("404", Basic404);
		PopulateMimeTypes();
		JNet::Connection *c;
		Sock.setTimeout(1);
		Sock.listen(port);
		int pnum = 0;
		int numCPU = std::thread::hardware_concurrency();
/*		if(threaded)
		{
		}
		else
		{
			while(pnum <= numCPU && fork())
			{
				pnum++;
			}
			if(pnum == 0)
			{
				return;
			}
		}*/
		std::vector<boost::thread> b(numCPU);
		for( ;pnum < numCPU; pnum++)
		{
			b[pnum] = boost::thread(&worker);
		}
		std::string str;
		PageMap *pagemap;
		int code;
		std::string msg;
		while(true)
		{
			Sock.HandleIO();
			for(int i=0;i<Sock.GetNumConnections();i++)
			{
				c = Sock.GetConnection(i);
				code = 200;
				msg = "";
				if(c->DataReady())
				{
					pagemap = nullptr;
					Request *request = new Request();
					str = c->GetLine();
					//std::cout << "Got request: " << str << std::endl;
					try
					{
						request->create(str);
						while((str = c->GetLine()) != "")
						{
							//std::cout << "Got header: " << str << std::endl;
							request->addHeader(str);
						}
						if((str = c->GetLine()) != "")
						{
							//std::cout << "Got vars: " << str << std::endl;
							request->addRequestVars(str);
						}
					}
					catch(HTTPException &e)
					{
						std::stringstream s;
						s << "/" << e.getCode();
						pagemap = &BindMap[s.str()];
						code = e.getCode();
						msg = e.getMsg();
					}
					if(pagemap == nullptr)
					{
						if((pagemap = GetPageMap(request->getLocation())) == nullptr)
						{
							pagemap = &BindMap["/404"];
							code = 404;
						}
					}
					RequestMutex.lock();
					RequestQueue.push(std::make_tuple(pagemap, c, request, code, msg));
					RequestMutex.unlock();
				}
			}
			CloseMutex.lock();
			while(!CloseQueue.empty())
			{
				//std::cout << "Closed : " << ++i << std::endl;
				Sock.CloseConnection(CloseQueue.front());
				CloseQueue.pop();
			}
			CloseMutex.unlock();
		}
	}
}
