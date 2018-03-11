#include "esgit/Blob.h"
#include "esgit/Exception.h"

namespace esgit {

Blob::Blob(git_blob *blob)
    : Object(reinterpret_cast<git_object*>(blob))
{
}

Blob::~Blob()
{
}

Blob::Ptr Blob::fromObject(Object::Ptr object)
{
	Blob::Ptr blob;
	if (object->isBlob()) {
		git_object *copy;
		esGitThrow(git_object_dup(&copy, object->data()));
		blob.reset(new Blob(reinterpret_cast<git_blob*>(copy)));
	}
	return blob;
}

const void* Blob::rawContent() const
{
    return git_blob_rawcontent(data());
}

std::string Blob::content() const
{
    return std::string(static_cast<const char *>(rawContent()), rawSize());
}

int Blob::rawSize() const
{
    return git_blob_rawsize(data());
}

git_blob* Blob::data() const
{
    return reinterpret_cast<git_blob*>(Object::data());
}

const git_blob* Blob::constData() const
{
    return reinterpret_cast<git_blob*>(Object::data());
}


}