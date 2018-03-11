#pragma once

#include <esgit/Oid.h>
#include <esgit/Exception.h>

#include <git2.h>

#include <memory>

namespace esgit {

class RevWalk
{
public:
	typedef std::shared_ptr<RevWalk> Ptr;

	enum SortMode
	{
		None = GIT_SORT_NONE,
		Topological = GIT_SORT_TOPOLOGICAL,
		Time = GIT_SORT_TIME,
		Reverse = GIT_SORT_REVERSE
	};

	typedef int SortModes;

	explicit RevWalk(git_revwalk *revwalk);

	~RevWalk();

	void reset() const;

	void push(const OId& oid) const;

	void pushHead() const;

	void hide(const OId& oid) const;

	void hideHead() const;

	OId::Ptr next() const;

	void setSorting(SortModes sortMode);

	git_revwalk* data() const;
	const git_revwalk* constData() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}