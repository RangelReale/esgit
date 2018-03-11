#include "esgit/Object.h"

namespace esgit
{

class Object::Private
{
public:
	Private(git_object *obj) :
		p(obj)
	{

	}

	~Private()
	{
		if (p)
		{
			git_object_free(p);
		}
	}

	git_object *p;
};

// git_object_free() is automatically invoked on the pointer when
// it is no more referenced.
Object::Object(git_object *object)
    : _pimpl(new Private(object))
{
}

Object::~Object()
{
}

Object::Type Object::type() const
{
    Type t = BadType;
    if (!isNull()) {
        t = resolveType(git_object_type(_pimpl->p));
    }

    return t;
}

Object::Type Object::resolveType(git_otype rawType)
{
    switch (rawType) {
    case GIT_OBJ_COMMIT:
        return CommitType;
    case GIT_OBJ_TAG:
        return TagType;
    case GIT_OBJ_TREE:
        return TreeType;
    case GIT_OBJ_BLOB:
        return BlobType;
    default:
        return BadType;
    }
}

/*
Tag Object::toTag() const
{
    Tag tag;
    if (isTag()) {
        tag.d = d;
    }
    return tag;
}
*/

bool Object::isNull() const
{
    return _pimpl->p == nullptr;
}

OId::Ptr Object::oid() const
{
    return OId::create(git_object_id(_pimpl->p));
}

bool Object::isCommit() const
{
    return type() == CommitType;
}

bool Object::isTag() const
{
    return type() == TagType;
}

bool Object::isTree() const
{
    return type() == TreeType;
}

bool Object::isBlob() const
{
    return type() == BlobType;
}

std::string Object::typeString() const
{
    return std::string(git_object_type2string(git_object_type(_pimpl->p)));
}

git_object* Object::data() const
{
    return _pimpl->p;
}

const git_object* Object::constData() const
{
	return _pimpl->p;
}

bool operator ==(const Object &o1, const Object &o2)
{
    return (o1.oid() == o2.oid());
}

bool operator !=(const Object &o1, const Object &o2)
{
    return !(operator ==(o1, o2));
}

}