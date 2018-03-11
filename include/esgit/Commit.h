#pragma once

#include "esgit/Object.h"
#include "esgit/OId.h"
#include "esgit/Signature.h"

#include "git2.h"

#include <memory>
#include <string>

namespace esgit {

class Commit : public Object
{
public:
	typedef std::shared_ptr<Commit> Ptr;

	/**
	* Creates a Commit that points to commit. The pointer object becomes managed by
	* this Commit, and must not be passed to another Commit or closed outside this
	* object.
	*/
	explicit Commit(git_commit *commit);

	/**
	* Destroys the object.
	*/
	~Commit();

	static Commit::Ptr fromObject(Object::Ptr object);

	/**
	* Get the id of a commit.
	*/
	OId::Ptr oid() const;

	/**
	* Get the full message of a commit.
	*/
	std::string message() const;

	/**
	* Get the short commit message.
	*
	* Get the first part of the commit message (similar to
	* git log --oneline). The string is further cut when a
	* linebreak is found.
	*
	* @param maxLen maximal length of the resulting string.
	* Default is 80 characters.
	*
	* @return the short message
	*/
	std::string shortMessage(int maxLen = 80) const;

	/**
	* Get the commit time (i.e. committer time) of this commit.
	*/
	git_time_t dateTime() const;

	/**
	* Get the timezone offset.
	*
	* Get the timezone offset (i.e. committer's preferred timezone)
	* of this commit.
	*
	* @return positive or negative timezone offset, in minutes from UTC
	*/
	int timeOffset() const;

	/**
	* Get the committer signature of this commit.
	*/
	Signature::Ptr committer() const;

	/**
	* Get the author signature of this commit.
	*/
	Signature::Ptr author() const;

	/**
	* Get the tree pointed to by this commit.
	*
	* @throws Exception
	*/
	//Tree tree() const;

	/**
	* Get the number of parents of this commit
	*/
	unsigned int parentCount() const;

	/**
	* Get the specified parent of the commit.
	*
	* This method returns the nth parent of this commit or, if no
	* parent can be found, an empty commit.
	*
	* @param n the position of the parent
	* @return the parent commit or an empty commit
	* @throws Exception
	*/
	Commit::Ptr parent(unsigned n) const;

	/**
	* Get the OId of the specified parent of the commit.
	*
	* This method returns the Oid of the nth parent of this commit or,
	* if no parent can be found, an empty OId.
	*
	* @param n the position of the parent
	* @return the OId of the parent commit or an empty OId
	* @throws Exception
	*/
	OId::Ptr parentId(unsigned n) const;

	/**
	* Amends an existing commit.
	*
	* Only the arguments that are provided are used. Arguments left to their default values
	* mean that the property in the Commit is not changed.
	*
	* @param tree The Tree to be used to amend the Commit.
	* @param ref Name of the reference that will be updated to point to the amended Commit.
	*        See Repository::createCommit.
	* @param message The message for the amended Commit.
	* @param author Author signature.
	* @param committer Committer signature.
	* @return The OId of the amended Commit.
	*
	* @see Repository::createCommit
	*/
	//OId amend(const Tree& tree = Tree(), const QString& ref = QString(), const QString& message = QString(), const Signature& author = Signature(), const Signature& committer = Signature());

	git_commit* data() const;
	const git_commit* constData() const;
};

}