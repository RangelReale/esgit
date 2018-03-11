#pragma once

#include <esgit/Object.h>

#include <memory>

namespace esgit {

/**
* @brief Wrapper class for git_blob.
*
* @ingroup LibQGit2
* @{
*/
class Blob : public Object
{
public:
	typedef std::shared_ptr<Blob> Ptr;

	/**
	* Create an Blob.
	*
	* Creates a Blob that points to the given git_blob.
	*/
	explicit Blob(git_blob *blob);

	/**
	* Destroy the object.
	*/
	~Blob();

	static Blob::Ptr fromObject(Object::Ptr object);

	/**
	* Get the raw content of this blob.
	*
	* This method returns a read-only buffer with the raw content
	* of the blob. This pointer is automatically freed when there
	* are no more objects referencing it. The pointer may be
	* invalidated at a later time (e.g. when changing the contents
	* of the blob).
	*
	* @return the pointer; NULL if the blob has no contents
	*/
	const void* rawContent() const;

	/**
	* @return The blob content as std::string.
	*/
	std::string content() const;

	/**
	* Get the size in bytes of the contents of a blob
	*
	* @return size on bytes
	*/
	int rawSize() const;

	git_blob* data() const;
	const git_blob* constData() const;
};


}