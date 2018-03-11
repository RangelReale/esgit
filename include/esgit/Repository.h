#pragma once

#include <esgit/Commit.h>
#include <esgit/RevWalk.h>

#include <git2.h>

#include <memory>
#include <string>
#include <list>

namespace esgit {

class Repository
{
public:
	typedef std::shared_ptr<Repository> Ptr;

	explicit Repository(git_repository *repository, bool own = false);
	~Repository();

	static Repository::Ptr open(const std::string &path);
	static Repository::Ptr init(const std::string &path, bool isBare = false);

	static std::string discover(const std::string& startPath,
		bool acrossFs = false,
		const std::list<std::string> ceilingDirs = std::list<std::string>());

	static Repository::Ptr discoverAndOpen(const std::string &startPath,
		bool acrossFs = false,
		const std::list<std::string> ceilingDirs = std::list<std::string>());

	bool isHeadDetached() const;

	bool isHeadUnborn() const;

	bool isEmpty() const;

	bool isBare() const;

	std::string path() const;

	std::string workDirPath() const;

	Commit::Ptr lookupCommit(OId::Ptr oid) const;

	RevWalk::Ptr revWalk();

	git_repository *data();
	const git_repository *constData();
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}