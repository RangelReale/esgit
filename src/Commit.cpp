#include "esgit/Commit.h"
#include "esgit/Exception.h"

namespace esgit {

Commit::Commit(git_commit *commit)
    : Object(reinterpret_cast<git_object*>(commit))
{
}

Commit::~Commit()
{
}

Commit::Ptr Commit::fromObject(Object::Ptr object)
{
	Commit::Ptr commit;
	if (object->isCommit()) {
		git_object *copy;
		esGitThrow(git_object_dup(&copy, object->data()));
		commit.reset(new Commit(reinterpret_cast<git_commit*>(copy)));
	}
	return commit;
}

OId::Ptr Commit::oid() const
{
    return OId::create(git_commit_id(data()));
}

std::string Commit::message() const
{
    return std::string(git_commit_message(data()));
}

std::string Commit::shortMessage(int maxLen) const
{
	std::string msg = message();
	return std::string(msg.begin(), std::find(msg.begin(), msg.end(), '\n')).substr(0, maxLen);
}

git_time_t Commit::dateTime() const
{
	return git_commit_time(data());
}

int Commit::timeOffset() const
{
    return git_commit_time_offset(data());
}

Signature::Ptr Commit::committer() const
{
    return Signature::Ptr(new Signature(git_commit_committer(data())));
}

Signature::Ptr Commit::author() const
{
    return Signature::Ptr(new Signature(git_commit_author(data())));
}

Tree::Ptr Commit::tree() const
{
    git_tree *tree;
    esGitThrow(git_commit_tree(&tree, data()));
    return Tree::Ptr(new Tree(tree));
}

unsigned int Commit::parentCount() const
{
    return git_commit_parentcount(data());
}

Commit::Ptr Commit::parent(unsigned n) const
{
    git_commit *parent;
    esGitThrow(git_commit_parent(&parent, data(), n));
    return Commit::Ptr(new Commit(parent));
}

OId::Ptr Commit::parentId(unsigned n) const
{
    return OId::create(git_commit_parent_id(data(), n));
}

/*
OId Commit::amend(const Tree& tree, const QString& ref, const QString& message, const Signature& author, const Signature& committer)
{
    OId oid;
    qGitThrow(git_commit_amend(oid.data(), constData(), ref.isEmpty() ? NULL : PathCodec::toLibGit2(ref).constData(), author.data(), committer.data(),
                               NULL, message.isNull() ? NULL : message.toUtf8().constData(), tree.constData()));
    return oid;
}
*/

git_commit* Commit::data() const
{
    return reinterpret_cast<git_commit*>(Object::data());
}

const git_commit* Commit::constData() const
{
    return reinterpret_cast<git_commit*>(Object::data());
}



}