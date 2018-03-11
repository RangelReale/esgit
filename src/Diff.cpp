#include "esgit/Diff.h"

namespace esgit {

class Diff::Private
{
public:
	Private(git_diff *diff) :
		p(diff)
	{

	}

	~Private()
	{
		git_diff_free(p);
	}

	git_diff *p;
};

Diff::Diff(git_diff *diff) :
	_pimpl(new Private(diff))
{
}

Diff::~Diff()
{

}

size_t Diff::numDeltas() const
{
	return git_diff_num_deltas(_pimpl->p);
}

DiffDelta::Ptr Diff::delta(size_t index) const
{
	return DiffDelta::Ptr(new DiffDelta(git_diff_get_delta(_pimpl->p, index)));
}

}
