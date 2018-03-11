#include "esgit/RevWalk.h"
#include "esgit/Repository.h"

namespace esgit {

class RevWalk::Private
{
public:
	Private(git_revwalk *revwalk) :
		p(revwalk), repository(new Repository(git_revwalk_repository(revwalk), false))
	{
		
	}

	~Private()
	{
		git_revwalk_free(p);
	}

	git_revwalk* p;
	Repository::Ptr repository;
};

RevWalk::RevWalk(git_revwalk *revwalk) :
	_pimpl(new Private(revwalk))
{
}

RevWalk::~RevWalk()
{
}

void RevWalk::reset() const
{
    git_revwalk_reset(_pimpl->p);
}

void RevWalk::push(const OId& oid) const
{
    esGitThrow(git_revwalk_push(_pimpl->p, oid.constData()));
}

void RevWalk::pushHead() const
{
    esGitThrow(git_revwalk_push_head(_pimpl->p));
}

void RevWalk::hide(const OId& oid) const
{
    esGitThrow(git_revwalk_hide(_pimpl->p, oid.constData()));
}

void RevWalk::hideHead() const
{
    esGitThrow(git_revwalk_hide_head(_pimpl->p));
}

OId::Ptr RevWalk::next() const
{
	git_oid oid;

    int err = git_revwalk_next(&oid, _pimpl->p);
	if (err == GIT_OK)
	{
		return OId::create(&oid);
	}
	return OId::Ptr();
}

Commit::Ptr RevWalk::nextCommit()
{
	auto oid = next();
	if (oid)
	{
		return _pimpl->repository->lookupCommit(oid);
	}
	return Commit::Ptr();
}

void RevWalk::setSorting(SortModes sm)
{
    git_revwalk_sorting(_pimpl->p, sm);
}

git_revwalk* RevWalk::data() const
{
    return _pimpl->p;
}

const git_revwalk* RevWalk::constData() const
{
	return _pimpl->p;
}

}