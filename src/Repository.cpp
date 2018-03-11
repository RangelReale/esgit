#include "esgit/Repository.h"
#include "esgit/Exception.h"
#include "esgit/Buffer.h"
#include "esgit/Util.h"

namespace esgit {

//
// Repository::Private
//
class Repository::Private
{
public:
	git_repository *p;
	bool own;
	Repository &owner;
	std::string path;

	Private(git_repository *repository, bool own, Repository &owner) :
		p(repository), own(own), owner(owner), path(git_repository_path(repository))
	{

	}

	~Private()
	{
		if (own) 
		{
			git_repository_free(p);
		}
	}
};

//
// Repository
//

Repository::Repository(git_repository *repository, bool own) :
	_pimpl(new Private(repository, own, *this))
{

}

Repository::~Repository()
{

}

Repository::Ptr Repository::open(const std::string &path)
{
	git_repository *ropen = nullptr;
	esGitThrow(git_repository_open(&ropen, path.c_str()));
	return Repository::Ptr(new Repository(ropen, true));
}


Repository::Ptr Repository::init(const std::string &path, bool isBare)
{
	git_repository *ropen = nullptr;
	esGitThrow(git_repository_init(&ropen, path.c_str(), isBare));
	return Repository::Ptr(new Repository(ropen, true));
}

std::string Repository::discover(const std::string& startPath,
	bool acrossFs,
	const std::list<std::string> ceilingDirs)
{
	Buffer repoPath;
	std::string joinedCeilingDirs = Util::join(ceilingDirs, std::string(1, GIT_PATH_LIST_SEPARATOR));
	esGitThrow(git_repository_discover(repoPath.data(), startPath.c_str(), acrossFs, joinedCeilingDirs.c_str()));
	return repoPath.asPath();
}

Repository::Ptr Repository::discoverAndOpen(const std::string &startPath,
	bool acrossFs,
	const std::list<std::string> ceilingDirs)
{
	return open(discover(startPath, acrossFs, ceilingDirs));
}

bool Repository::isHeadDetached() const
{
	return esGitThrow(git_repository_head_detached(_pimpl->p)) == 1;
}

bool Repository::isHeadUnborn() const
{
	return esGitThrow(git_repository_head_unborn(_pimpl->p)) == 1;
}

bool Repository::isEmpty() const
{
	return esGitThrow(git_repository_is_empty(_pimpl->p)) == 1;
}

bool Repository::isBare() const
{
	return esGitThrow(git_repository_is_bare(_pimpl->p)) == 1;
}

std::string Repository::path() const
{
	return std::string(git_repository_path(_pimpl->p));
}

std::string Repository::workDirPath() const
{
	return std::string(git_repository_workdir(_pimpl->p));
}

Commit::Ptr Repository::lookupCommit(OId::Ptr oid) const
{
	git_commit *commit = 0;
	esGitThrow(git_commit_lookup_prefix(&commit, _pimpl->p, oid->constData(), oid->length()));
	return Commit::Ptr(new Commit(commit));
}

RevWalk::Ptr Repository::revWalk()
{
	git_revwalk *revwalk = nullptr;
	esGitThrow(git_revwalk_new(&revwalk, _pimpl->p));
	return RevWalk::Ptr(new RevWalk(revwalk));
}

git_repository *Repository::data()
{
	return _pimpl->p;
}

const git_repository *Repository::constData()
{
	return _pimpl->p;
}

}