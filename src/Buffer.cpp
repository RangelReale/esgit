#include "esgit/Buffer.h"

namespace esgit {

class Buffer::Private
{
public:
	Private(git_buf *buf) :
		p(buf)
	{
		if (p == nullptr) {
			p = static_cast<git_buf*>(malloc(sizeof(git_buf)));
			p->ptr = nullptr;
			p->size = 0;
			p->asize = 0;
		}
	}

	~Private()
	{
		git_buf_free(p);
	}

	git_buf *p;
};


Buffer::Buffer() :
	_pimpl(new Private(nullptr))
{
}

Buffer::Buffer(git_buf *buf) : 
	_pimpl(new Private(buf))
{

}

Buffer::~Buffer()
{
}

std::string Buffer::asString() const
{
	return std::string(_pimpl->p->ptr, _pimpl->p->size);
}

git_buf* Buffer::data()
{
	return _pimpl->p;
}

}