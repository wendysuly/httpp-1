/*************************
 *         htt++         *
 *************************
 *    Utilities Module   *
 *      Source File      *
 *************************
 * www.git-hub.com/httpp *
 *************************/

#include "util.hpp"

namespace httpp
{
	std::string strToLower(const std::string &s)
	{
		std::string ret;
		int len = s.length();
		for(int i=0;i<len;i++)
			ret+=tolower(s[i]);
		return ret;
	}
}
