#pragma once

#include <esgit/Object.h>
#include <esgit/TreeEntry.h>

#include <memory>

namespace esgit {

class Tree : public Object
{
public:
	typedef std::shared_ptr<Tree> Ptr;

	/**
	* Creates a Tree that points to tree. The pointer object becomes managed by
	* this Tree, and must not be passed to another Tree or closed outside this
	* object.
	*/
	explicit Tree(git_tree *tree);

	/**
	* Copy constructor; creates a copy of the object, sharing the same underlaying data
	* structure.
	*/
	Tree(const Tree& other);

	/**
	* Destroys the object.
	*/
	~Tree();


	static Tree::Ptr fromObject(Object::Ptr object);

	/**
	* * Get the id of a tree.
	* * @return object identity for the tree.
	* */
	OId::Ptr oid();

	/**
	* Get the number of entries listed in a tree
	* @return the number of entries in the tree
	*/
	size_t entryCount();

	/**
	* Lookup a tree entry by its filename
	* @param filename the filename of the desired entry
	* @return the tree entry; NULL if not found
	*/
	TreeEntry::Ptr entryByName(const std::string& fileName) const;

	/**
	* Lookup a tree entry by its position in the tree
	* @param idx the position in the entry list
	* @return the tree entry; NULL if not found
	*/
	TreeEntry::Ptr entryByIndex(int idx) const;

	git_tree* data() const;
	const git_tree* constData() const;
};

}