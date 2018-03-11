#include "esgit/Init.h"

#include "git2.h"

namespace esgit {

Init::Init()
{
	git_libgit2_init();
}

Init::~Init()
{
	git_libgit2_shutdown();
}

}