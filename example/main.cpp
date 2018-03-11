#include <esgit/ESGit.h>

#include <iostream>

int main(int argc, char *argv)
{
	try
	{
		esgit::Init init;
		auto repo = esgit::Repository::open("M:\\prog\\src\\OpenXcom");

		auto revwalk = repo->revWalk();
		revwalk->pushHead();

		esgit::Commit::Ptr walk = revwalk->nextCommit();
		for (; walk; walk = revwalk->nextCommit())
		{
			std::cout << 
				walk->oid()->format() <<
				" -- " <<
				walk->shortMessage() <<
				std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	std::cout << "FINISHED...";
	std::cin.ignore();

	return 0;
}