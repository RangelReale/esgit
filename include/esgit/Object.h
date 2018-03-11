#pragma once

#include <memory>

namespace esgit {

class Object
{
public: 
	typedef std::shared_ptr<Object> Ptr;

	Object();
};


}