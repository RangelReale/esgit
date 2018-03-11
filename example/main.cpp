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

		esgit::OId::Ptr walkoid = revwalk->next();
		for (; walkoid; walkoid = revwalk->next())
		{
			std::cout << walkoid->format() << std::endl;
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