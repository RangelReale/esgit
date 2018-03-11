#include "esgit/Signature.h"
#include "esgit/Exception.h"

namespace esgit {


class Signature::Private 
{
public:
    Private(const git_signature *signature, bool own) :
        p(const_cast<git_signature*>(signature)), own(own)
    {
    }

	~Private()
	{
		if (own) {
			git_signature_free(p);
		}
	}

    git_signature *p;
	bool own;
};

Signature::Signature(const std::string& name, const std::string& email, git_time dateTime)
{
    git_signature *sig = 0;
    esGitThrow(git_signature_new(&sig, name.c_str(), email.c_str(), dateTime.time, dateTime.offset));
	_pimpl.reset(new Private(sig, true));
}

Signature::Signature(const std::string& name, const std::string& email)
{
    git_signature *sig = 0;
    esGitThrow(git_signature_now(&sig, name.c_str(), email.c_str()));
	_pimpl.reset(new Private(sig, true));
}

Signature::Signature(const git_signature *signature) :
    _pimpl(new Private(signature, false))
{
}

Signature::~Signature()
{

}

std::string Signature::name() const
{
    std::string ret;
    if (_pimpl->p) {
        ret = std::string(_pimpl->p->name);
    }
    return ret;
}

std::string Signature::email() const
{
	std::string ret;
    if (_pimpl->p) {
        ret = std::string(_pimpl->p->email);
    }
    return ret;
}

git_time Signature::when() const
{
	git_time dt{ 0,0,0 };
    if (_pimpl->p) {
		return _pimpl->p->when;
    }
    return dt;
}

const git_signature *Signature::data() const
{
    return _pimpl->p;
}

}