#include "esgit/DiffHunk.h"
#include "esgit/Exception.h"

namespace esgit {

class DiffHunk::Private
{
public:
	Private(git_patch *patch, size_t hunk_idx, const git_diff_hunk *hunk) :
		patch(patch), hunk_idx(hunk_idx), p(const_cast<git_diff_hunk*>(hunk))
	{

	}

	~Private()
	{

	}

	git_patch *patch;
	size_t hunk_idx;
	git_diff_hunk *p;
};

DiffHunk::DiffHunk(git_patch *patch, size_t hunk_idx, const git_diff_hunk *hunk) :
	_pimpl(new Private(patch, hunk_idx, hunk))
{

}

DiffHunk::~DiffHunk()
{

}

size_t DiffHunk::numLines() const
{
	return git_patch_num_lines_in_hunk(_pimpl->patch, _pimpl->hunk_idx);
}

DiffLine::Ptr DiffHunk::line(size_t index) const
{
	const git_diff_line *line = nullptr;
	esGitThrow(git_patch_get_line_in_hunk(&line, _pimpl->patch, _pimpl->hunk_idx, index));

	return DiffLine::Ptr(new DiffLine(line));
}

git_diff_hunk* DiffHunk::data() const
{
	return _pimpl->p;
}

const git_diff_hunk* DiffHunk::constData() const
{
	return _pimpl->p;
}

}