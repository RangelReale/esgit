#include <esgit/ESGit.h>

#include <iostream>
#include <ctime>

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
			std::time_t now = (time_t)(walk->author()->when().time + (walk->author()->when().offset * 60));
			std::tm * ptm = std::localtime(&now);
			char buffer[32];
			// Format: Mo, 15.06.2009 20:20:00
			std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);

			std::cout << 
				walk->oid()->format() <<
				" -- " <<
				walk->author()->name() <<
				" -- " <<
				buffer <<
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