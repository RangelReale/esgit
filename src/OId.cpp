#include "esgit/OId.h"
#include "esgit/Exception.h"

#include <algorithm>

namespace esgit {

class OId::Private
{
public:
	Private(const git_oid* oid, int len) :
		p(nullptr), len(len)
	{
		if (oid != 0)
		{ 
			if (this->len < 0)
				this->len = sizeof(git_oid);
			p = static_cast<git_oid*>(malloc(sizeof(git_oid)));
			git_oid_cpy(p, oid);
		}
		else
		{
			this->len = 0;
		}
	}

	~Private()
	{
		if (p)
			free(p);
	}


	git_oid *p;
	int len;
};

OId::OId(const git_oid* oid, int len)
    : _pimpl(new Private(oid, len))
{
}

OId::~OId()
{
}

bool OId::isValid() const
{
	return _pimpl->p != nullptr;
}

OId::Ptr OId::create(const git_oid *oid, int len)
{
	OId::Ptr ret;
	if (oid != nullptr && !git_oid_iszero(oid))
	{
		ret.reset(new OId(oid, len));
	}
	return ret;
}

OId::Ptr OId::fromHex(const std::string& hex)
{
    int len = std::min(hex.size(), static_cast<size_t>(GIT_OID_HEXSZ));
	git_oid oid;
    esGitThrow(git_oid_fromstrn(&oid, hex.c_str(), len));    
	return OId::create(&oid, len);
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
	return OId::create(&oid, GIT_OID_HEXSZ);
}

std::string OId::format() const
{
	char *out = static_cast<char*>(malloc(_pimpl->len+1));
	git_oid_nfmt(out, _pimpl->len, _pimpl->p);
	out[_pimpl->len] = '\0';
    std::string ret(out);
	free(out);
	return ret;
}

std::string OId::pathFormat() const
{
	char *out = static_cast<char*>(malloc(GIT_OID_HEXSZ + 2));
	git_oid_pathfmt(out, _pimpl->p);
	out[GIT_OID_HEXSZ+1] = '\0';
	std::string ret(out);
	free(out);
	return ret;
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

int OId::length() const
{
	return _pimpl->len;
}

}