#include "esgit/Buffer.h"

namespace esgit {

Buffer::Buffer()
{
	git_buf temp = GIT_BUF_INIT_CONST(0, 0);
	d = temp;
}

Buffer::Buffer(git_buf buf) : 
	d(buf)
{

}

Buffer::~Buffer()
{
	git_buf_free(&d);
}

std::string Buffer::asPath() const
{
	return std::string(d.ptr);
}

git_buf* Buffer::data()
{
	return &d;
}

}