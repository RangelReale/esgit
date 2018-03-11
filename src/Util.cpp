#include "esgit/Util.h"

#include <sstream>

namespace esgit {
namespace Util {

std::string join(std::list<std::string> list, const std::string &sep)
{
	std::stringstream out;
	for (auto iter = list.begin(); iter != list.end(); iter++) 
	{
		if (iter != list.begin()) out << sep;
		out << *iter;
	}
	return out.str();
}

} }