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
	std::string strToLower(std::string s)
	{
		int len = s.length();
		for(int i=0;i<len;i++)
			s[i]=tolower(s[i]);
		return s;
	}
}
