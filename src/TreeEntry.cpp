#include "esgit/TreeEntry.h"
#include "esgit/Exception.h"

namespace esgit {

class TreeEntry::Private
{
public:
	Private(git_tree *tree, const git_tree_entry *treeEntry, bool own) :
		tree(tree), p(const_cast<git_tree_entry*>(treeEntry)), own(own)
	{


	}

	~Private()
	{
		if (own)
			git_tree_entry_free(p);
	}

	git_tree *tree;
	git_tree_entry *p;
	bool own;
};


TreeEntry::TreeEntry(git_tree *tree, const git_tree_entry* treeEntry, bool own)
	: _pimpl(new Private(tree, treeEntry, own))
{
}

TreeEntry::~TreeEntry()
{
}

unsigned int TreeEntry::attributes() const
{
    return git_tree_entry_filemode(_pimpl->p);
}

const std::string TreeEntry::name() const
{
    return std::string(git_tree_entry_name(_pimpl->p));
}

OId::Ptr TreeEntry::oid() const
{
    return OId::Ptr(new OId(git_tree_entry_id(_pimpl->p)));
}

Object::Type TreeEntry::type() const
{
    return Object::resolveType(git_tree_entry_type(_pimpl->p));
}

Object::Ptr TreeEntry::object()
{
    git_object *obj;
    esGitThrow(git_tree_entry_to_object(&obj, git_tree_owner(_pimpl->tree), _pimpl->p));
    return Object::Ptr(new Object(obj));
}

const git_tree_entry* TreeEntry::data() const
{
    return _pimpl->p;
}

}