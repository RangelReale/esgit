#include "esgit/DiffLine.h"
#include "esgit/Exception.h"

namespace esgit {

class DiffLine::Private
{
public:
	Private(const git_diff_line *line) :
		p(const_cast<git_diff_line*>(line))
	{

	}

	~Private()
	{

	}

	git_diff_line *p;
};

DiffLine::DiffLine(const git_diff_line *line) :
	_pimpl(new Private(line))
{

}

DiffLine::~DiffLine()
{

}

git_diff_line* DiffLine::data() const
{
	return _pimpl->p;
}

const git_diff_line* DiffLine::constData() const
{
	return _pimpl->p;
}

}