#pragma once

#include "git2.h"

#include <string>
#include <memory>

namespace esgit {

class OId
{
public:
	typedef std::shared_ptr<OId> Ptr;

	explicit OId(const git_oid *oid = 0);

	~OId();

	static OId::Ptr fromHex(const std::string& hex);

	static OId::Ptr fromString(const std::string& string);

	static OId::Ptr fromRawData(const std::string& raw);

	bool isValid() const;

	/**
	* Format a OId into a hex string.
	*/
	std::string format() const;

	/**
	* Format a git_oid into a loose-object path string.
	*
	* The resulting string is "aa/...", where "aa" is the first two
	* hex digitis of the oid and "..." is the remaining 38 digits.
	*/
	std::string pathFormat() const;

	git_oid* data();
	const git_oid* constData() const;

	//int length() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};


}