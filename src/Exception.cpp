#include "esgit/Exception.h"

#include <git2.h>

namespace esgit {

Exception::Exception() :
	_category(None)
{
	const git_error *err = giterr_last();

	if (err != NULL) {
		_message = std::string(err->message);

		switch (err->klass) {
		case GITERR_NOMEMORY:   _category = NoMemory; break;
		case GITERR_OS:         _category = OS; break;
		case GITERR_INVALID:    _category = Invalid; break;
		case GITERR_REFERENCE:  _category = Reference; break;
		case GITERR_ZLIB:       _category = ZLib; break;
		case GITERR_REPOSITORY: _category = Repository; break;
		case GITERR_CONFIG:     _category = Config; break;
		case GITERR_REGEX:      _category = RegEx; break;
		case GITERR_ODB:        _category = ODB; break;
		case GITERR_INDEX:      _category = Index; break;
		case GITERR_OBJECT:     _category = Object; break;
		case GITERR_NET:        _category = Net; break;
		case GITERR_TAG:        _category = Tag; break;
		case GITERR_TREE:       _category = Tree; break;
		case GITERR_INDEXER:    _category = Indexer; break;
		case GITERR_SSL:        _category = SSL; break;
		case GITERR_SUBMODULE:  _category = Submodule; break;
		case GITERR_THREAD:     _category = Thread; break;
		case GITERR_STASH:      _category = Stash; break;
		case GITERR_CHECKOUT:   _category = Checkout; break;
		case GITERR_FETCHHEAD:  _category = FetchHead; break;
		case GITERR_MERGE:      _category = Merge; break;
		case GITERR_SSH:        _category = SSH; break;
		case GITERR_FILTER:     _category = Filter; break;
		case GITERR_REVERT:     _category = Revert; break;
		case GITERR_CALLBACK:   _category = Callback; break;
		case GITERR_CHERRYPICK: _category = Cherrypick; break;
		case GITERR_NONE:
		default:                _category = None; break;
		}

		giterr_clear();
	}
}

Exception::Exception(const std::string& message, Category category) :
	_message(message),
	_category(category)
{
}

Exception::~Exception() throw()
{
}

const char *Exception::what() const throw()
{
	return _message.c_str();
}

const std::string &Exception::message() const throw()
{
	return _message;
}

Exception::Category Exception::category() const throw()
{
	return _category;
}

}