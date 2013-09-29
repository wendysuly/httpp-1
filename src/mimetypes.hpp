#pragma once

/*************************
 *         htt++         *
 *************************
 *      MIME Module      *
 *      Source File      *
 *************************/

#include <sprawl/multiaccess/multiaccess.hpp>
#include <boost/thread/mutex.hpp>

namespace httpp
{
	class MimeMap
	{
	public:
		MimeMap(const std::string &ext, const std::string &type) : m_ext(ext), m_type(type) {}
		std::string getExtension(){ return m_ext; }
		std::string getMimeType(){ return m_type.c_str(); }
	private:
		std::string m_ext;
		std::string m_type;
	};

	extern sprawl::multiaccess::multiaccess_map<MimeMap> MimeTypes;

	void PopulateMimeTypes();
}
