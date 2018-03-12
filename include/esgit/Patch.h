#pragma once

#include <esgit/DiffDelta.h>
#include <esgit/Buffer.h>
#include <esgit/DiffHunk.h>

#include <git2.h>

#include <memory>

namespace esgit {

class Patch
{
public:
	typedef std::shared_ptr<Patch> Ptr;

	Patch(const git_patch *p);

	~Patch();

	DiffDelta::Ptr delta() const;

	Buffer::Ptr format();

	size_t numHunks() const;
	DiffHunk::Ptr hunk(size_t index) const;

	git_patch* data() const;
	const git_patch* constData() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}