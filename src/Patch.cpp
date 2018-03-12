#include "esgit/Patch.h"
#include "esgit/Exception.h"

namespace esgit {

class Patch::Private
{
public:
	Private(const git_patch *patch) :
		p(const_cast<git_patch*>(patch))
	{

	}

	~Private()
	{
		git_patch_free(p);
	}

	git_patch *p;
};

Patch::Patch(const git_patch *patch) :
	_pimpl(new Private(patch))
{

}

Patch::~Patch()
{

}

DiffDelta::Ptr Patch::delta() const
{
	return DiffDelta::Ptr(new DiffDelta(git_patch_get_delta(_pimpl->p)));
}


Buffer::Ptr Patch::format()
{
	Buffer::Ptr buf(new Buffer);
	esGitThrow(git_patch_to_buf(buf->data(), _pimpl->p));
	return buf;
}

git_patch* Patch::data() const
{
	return _pimpl->p;
}

const git_patch* Patch::constData() const
{
	return _pimpl->p;
}


}