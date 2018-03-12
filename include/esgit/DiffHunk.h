#pragma once

#include <esgit/DiffLine.h>

#include <git2.h>

#include <memory>

namespace esgit {

class DiffHunk
{
public:
	typedef std::shared_ptr<DiffHunk> Ptr;

	DiffHunk(git_patch *patch, size_t hunk_idx, const git_diff_hunk *hunk);
	~DiffHunk();

	size_t numLines() const;
	DiffLine::Ptr line(size_t index) const;

	git_diff_hunk* data() const;
	const git_diff_hunk* constData() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}