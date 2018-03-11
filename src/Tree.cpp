#include "esgit/Tree.h"

namespace esgit {

Tree::Tree(git_tree *tree)
    : Object(reinterpret_cast<git_object*>(tree))
{
}

Tree::~Tree()
{
}

Tree::Ptr Tree::fromObject(Object::Ptr object)
{
	Tree::Ptr tree;
	if (object->isTree()) {
		tree.reset(new Tree(reinterpret_cast<git_tree*>(object->data())));
	}
	return tree;
}

OId::Ptr Tree::oid()
{
    return OId::Ptr(new OId(git_tree_id(data())));
}

size_t Tree::entryCount()
{
    return git_tree_entrycount(data());
}

TreeEntry::Ptr Tree::entryByName(const std::string& fileName) const
{
    return TreeEntry::Ptr(new TreeEntry(data(), git_tree_entry_byname(constData(), fileName.c_str())));
}

TreeEntry::Ptr Tree::entryByIndex(int idx) const
{
    return TreeEntry::Ptr(new TreeEntry(data(), git_tree_entry_byindex(data(), idx)));
}

git_tree* Tree::data() const
{
    return reinterpret_cast<git_tree*>(Object::data());
}

const git_tree* Tree::constData() const
{
    return reinterpret_cast<git_tree*>(Object::data());
}


}