#pragma once

#include <exception>
#include <string>

namespace esgit {

class Exception : std::exception
{
public:
	enum Category {
		None,
		NoMemory,
		OS,
		Invalid,
		Reference,
		ZLib,
		Repository,
		Config,
		RegEx,
		ODB,
		Index,
		Object,
		Net,
		Tag,
		Tree,
		Indexer,
		SSL,
		Submodule,
		Thread,
		Stash,
		Checkout,
		FetchHead,
		Merge,
		SSH,
		Filter,
		Revert,
		Callback,
		Cherrypick
	};

	Exception();
	Exception(const std::string& message, Category category = None);
	~Exception() throw();

	const char *what() const throw();

	const std::string &message() const throw();
	Category category() const throw();
private:
	std::string _message;
	Category _category;
};

inline int esGitThrow(int ret) { if (ret < 0) throw Exception(); return ret; }

inline void esGitEnsureValue(int value, int ret) { if (esGitThrow(ret) != value) throw Exception(); }

}