/*************************
 *         htt++         *
 *************************
 *      MIME Module      *
 *      Source File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#ifndef MIMETYPES_HPP_
#define MIMETYPES_HPP_

#include "jhash/JHash.hpp"

namespace httpp
{
	class MimeMap
	{
	public:
		MimeMap(std::string ext, std::string type) : m_ext(ext), m_type(type) {}
		std::string getExtension(){ return m_ext; }
		std::string getMimeType(){ return m_type.c_str(); }
	private:
		std::string m_ext;
		std::string m_type;
	};

	extern JHash::string_map<MimeMap> MimeTypes;

	void PopulateMimeTypes();
}

#endif /* MIMETYPES_HPP_ */
