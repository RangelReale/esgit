#pragma once

#include <git2.h>

#include <memory>
#include <string>

namespace esgit {

class Buffer
{
public:
	typedef std::shared_ptr<Buffer> Ptr;

	Buffer();
	explicit Buffer(git_buf *buf);
	~Buffer();

	std::string asString() const;

	git_buf* data();
private:
	class Private;
	std::unique_ptr<Private> _pimpl;

	git_buf d;
};

}