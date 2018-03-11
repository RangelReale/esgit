#pragma once

#include <memory>

namespace esgit {

class Repository
{
public:
	typedef std::shared_ptr<Repository> Ptr;

	Repository();
};

}