#include "esgit/Diff.h"
#include "esgit/Exception.h"

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

Patch::Ptr Diff::patch(size_t deltaIndex) const
{
	git_patch *patch = nullptr;
	esGitThrow(git_patch_from_diff(&patch, _pimpl->p, deltaIndex));

	return Patch::Ptr(new Patch(patch));
}


Buffer::Ptr Diff::format(Format fmt)
{
	Buffer::Ptr buf(new Buffer);
	esGitThrow(git_diff_to_buf(buf->data(), _pimpl->p, git_diff_format_t(fmt)));
	return buf;
}

git_diff *Diff::data() const
{
	return _pimpl->p;
}

const git_diff *Diff::constData() const
{
	return _pimpl->p;
}


}
