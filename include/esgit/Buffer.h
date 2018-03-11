#pragma once

#include <git2.h>

#include <string>

namespace esgit {

class Buffer
{
public:
	Buffer();
	explicit Buffer(git_buf buf);
	~Buffer();

	std::string asPath() const;

	git_buf* data();
private:
	git_buf d;

};

}