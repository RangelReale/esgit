#pragma once

#include <git2.h>

#include <memory>

namespace esgit {

class DiffLine
{
public:
	typedef std::shared_ptr<DiffLine> Ptr;

	DiffLine(const git_diff_line *line);
	~DiffLine();

	git_diff_line* data() const;
	const git_diff_line* constData() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}