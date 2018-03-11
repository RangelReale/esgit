#include "esgit/OId.h"
#include "esgit/Exception.h"

#include <algorithm>

namespace esgit {

class OId::Private
{
public:
	Private(const git_oid* oid) :
		p(nullptr)
	{
		if (oid != 0)
		{ 
			p = static_cast<git_oid*>(malloc(sizeof(git_oid)));
			git_oid_cpy(p, oid);
		}
	}

	~Private()
	{
		if (p)
			free(p);
	}


	git_oid *p;
};

OId::OId(const git_oid* oid)
    : _pimpl(new Private(oid))
{
}

OId::~OId()
{
}

bool OId::isValid() const
{
	return _pimpl->p != nullptr;
}

OId::Ptr OId::fromHex(const std::string& hex)
{
    int len = std::min(hex.size(), static_cast<size_t>(GIT_OID_HEXSZ));
	git_oid oid;
    esGitThrow(git_oid_fromstrn(&oid, hex.c_str(), len));    
	return OId::Ptr(new OId(&oid));
}

OId::Ptr OId::fromString(const std::string &string)
{
    return fromHex(string);
}

OId::Ptr OId::fromRawData(const std::string& raw)
{
    esGitThrow(raw.size() < GIT_OID_HEXSZ);
	git_oid oid;
	git_oid_cpy(&oid, reinterpret_cast<const git_oid*>(raw.c_str()));
	return OId::Ptr(new OId(&oid));
}

std::string OId::format() const
{
	char *out = static_cast<char*>(malloc(GIT_OID_HEXSZ+1));
    git_oid_fmt(out, _pimpl->p);
	out[GIT_OID_HEXSZ] = '\0';
    return std::string(out);
}

std::string OId::pathFormat() const
{
	char *out = static_cast<char*>(malloc(GIT_OID_HEXSZ + 2));
	git_oid_pathfmt(out, _pimpl->p);
	out[GIT_OID_HEXSZ+1] = '\0';
	return std::string(out);
}

git_oid* OId::data()
{
	return _pimpl->p;
}

const git_oid* OId::constData() const
{
	return _pimpl->p;
}

bool operator ==(const OId &oid1, const OId &oid2)
{
    return git_oid_cmp(oid1.constData(), oid2.constData()) == 0;
}

bool operator !=(const OId &oid1, const OId &oid2)
{
    return !(operator ==(oid1, oid2));
}

/*
int OId::length() const
{
    return d.length() * 2;
}
*/

}