#include "esgit/DiffDelta.h"

namespace esgit {

class DiffDelta::Private
{
public:
	Private(const git_diff_delta *d) :
		p(const_cast<git_diff_delta*>(d))
	{

	}

	git_diff_delta *p;
};

DiffDelta::DiffDelta(const git_diff_delta *d) :
	_pimpl(new Private(d))
{
}

DiffDelta::~DiffDelta()
{

}

DiffDelta::Type DiffDelta::type() const
{
	return DiffDelta::Type(_pimpl->p->status);
}

DiffFile::Ptr DiffDelta::oldFile() const
{
	return DiffFile::Ptr(new DiffFile(&_pimpl->p->old_file));
}

DiffFile::Ptr DiffDelta::newFile() const
{
	return DiffFile::Ptr(new DiffFile(&_pimpl->p->new_file));
}

git_diff_delta *DiffDelta::data() const
{
	return _pimpl->p;
}

const git_diff_delta *DiffDelta::constData() const
{
	return _pimpl->p;
}


}
