#pragma once

#include <esgit/OId.h>
#include <esgit/Object.h>

#include <git2.h>

#include <memory>
#include <string>

namespace esgit {

/**
* @brief Wrapper class for git_tree_entry.
* Represents a Git child tree entry, that can either point to another tree object or a blob.
*
* @ingroup LibQGit2
* @{
*/
class TreeEntry
{
public:
	typedef std::shared_ptr<TreeEntry> Ptr;

	explicit TreeEntry(git_tree *tree, const git_tree_entry* treeEntry, bool own = false);
	~TreeEntry();

	/**
	* Get the UNIX file attributes of a tree entry
	* @return attributes as an integer
	*/
	unsigned int attributes() const;

	/**
	* Get the filename of a tree entry
	* @return the name of the file
	*/
	const std::string name() const;

	/**
	* Get the id of the object pointed by the entry
	* @return the oid of the object
	*/
	OId::Ptr oid() const;

	/**
	* Get the type of the \c Object where this entry points to.
	* @note %Tree entries might not support all the possible object types.
	*/
	Object::Type type() const;

	/**
	* Convert a tree entry to the Object it points too.
	*
	* @param object pointer to the converted object
	* @return a reference to the pointed object in the repository
	* @throws LibQGit2::Exception
	*/
	Object::Ptr object();

	const git_tree_entry* data() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}