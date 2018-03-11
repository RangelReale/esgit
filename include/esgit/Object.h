#pragma once

#include "esgit/Repository.h"
#include "esgit/OId.h"

#include <git2.h>

#include <memory>

namespace esgit {

class Object
{
public: 
	typedef std::shared_ptr<Object> Ptr;

	enum Type {
		BadType,  ///< Not a valid Object type
		CommitType,
		TreeType,
		BlobType,
		TagType
	};

	explicit Object(git_object *object = 0);
	~Object();

	Type type() const;

	/**
	* Check if the pointer is null.
	*
	* Returns true if the git_object pointer owned by this
	* instance is null.
	*/
	bool isNull() const;

	/**
	* Get the OId (SHA1) of a repository object.
	*
	* This returns the OId of the object.
	* Remember that in-memory objects created by git_object_new()
	* do not have a SHA1 id until they are written on a repository.
	*
	* @return the OId of the object
	*/
	OId::Ptr oid() const;

	/**
	* Check if this is a commit.
	*
	* Returns true if the object represents a commit; false otherwise.
	*/
	bool isCommit() const;

	/**
	* Check if this is a tag.
	*
	* Returns true if the object represents a tag; false otherwise.
	*/
	bool isTag() const;

	/**
	* Check if this is a tree.
	*
	* Returns true if the object represents a tree; false otherwise.
	*/
	bool isTree() const;

	/**
	* Check if this is a blob.
	*
	* Returns true if the object represents a blob; false otherwise.
	*/
	bool isBlob() const;

	/**
	* Get the object type as a string.
	*/
	std::string typeString() const;

	Repository::Ptr owner() const;

	git_object* data() const;
	const git_object* constData() const;
private:
	static Type resolveType(git_otype);

	class Private;
	std::unique_ptr<Private> _pimpl;
};


}