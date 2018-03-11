#pragma once

#include <git2.h>

#include <memory>
#include <string>

namespace esgit {

class Signature
{
public:
	typedef std::shared_ptr<Signature> Ptr;

	/**
	* Construct a new action signature.
	*
	* @param name name of the person
	* @param email email of the person
	* @param dateTime time when the action happened
	* @throws LibQGit2::Exception
	*/
	Signature(const std::string& name, const std::string& email, git_time dateTime);

	/**
	* Construct a new action signature, using the `now` datetime generated by the
	* underlaying library.
	*
	* @param name name of the person
	* @param email email of the person
	* @throws LibQGit2::Exception
	*/
	Signature(const std::string& name, const std::string& email);

	/**
	* Create a reference to an existing \a signature; ownership of the pointer is not transferred.
	*/
	explicit Signature(const git_signature *signature = 0);

	~Signature();

	/**
	* Return the 'name' from this signature
	*/
	std::string name() const;

	/**
	* Return the 'email' from this signature
	*/
	std::string email() const;

	/**
	* Return the time stamp from this signature
	*/
	git_time when() const;

	const git_signature *data() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}