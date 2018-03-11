#include "esgit/DiffFile.h"

namespace esgit {

class DiffFile::Private
{
public:
	Private(git_diff_file *diff) :
		p(diff)
	{

	}

	git_diff_file *p;
};

DiffFile::DiffFile(git_diff_file *diff) : 
	_pimpl(new Private(diff))
{
}

DiffFile::~DiffFile()
{

}

std::string DiffFile::path() const
{
	return std::string(_pimpl->p->path);
}

OId::Ptr DiffFile::oid() const
{
	return OId::create(&_pimpl->p->id);
}

git_diff_file *DiffFile::data() const
{
	return _pimpl->p;
}

const git_diff_file *DiffFile::constData() const
{
	return _pimpl->p;
}


}
