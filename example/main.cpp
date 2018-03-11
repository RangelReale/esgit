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
		revwalk->setSorting(esgit::RevWalk::Time | esgit::RevWalk::Reverse);
		revwalk->pushHead();

		esgit::Commit::Ptr walk = revwalk->nextCommit();
		int ct = 0;
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

			if (ct == 2)
			{
				esgit::Diff::Ptr diff = repo->diffTrees(walk->parent(0)->tree(), walk->tree());

				for (int i = 0; i < diff->numDeltas(); i++)
				{
					esgit::DiffDelta::Ptr delta = diff->delta(i);

					std::cout << "DIFF DELTA: " << delta->newFile()->path() << std::endl;

					esgit::Object::Ptr deltaobj = repo->lookupAny(delta->newFile()->oid());
					if (deltaobj)
					{
						switch (deltaobj->type())
						{
						case esgit::Object::BlobType:
						{
							std::cout << "* FILE: " << std::endl;

							auto blob = esgit::Blob::fromObject(deltaobj);
							std::cout << blob->content();
							break;
						}
						case esgit::Object::TreeType:
							std::cout << "* TREE: " << std::endl;
							break;
						default:
							std::cout << "* OTHER: " << deltaobj->type() << std::endl;
							break;
						}
					}
				}


				/*
				esgit::Tree::Ptr tree = walk->tree();
				for (int i = 0; i < tree->entryCount(); ++i)
				{
					esgit::TreeEntry::Ptr entry(tree->entryByIndex(i));

					switch (entry->type())
					{
					case esgit::Object::BlobType:
					{
						std::cout << "* FILE: " << entry->name() << std::endl;

						auto blob = esgit::Blob::fromObject(entry->object());
						std::cout << blob->content();
						break;
					}
					case esgit::Object::TreeType:
						std::cout << "* TREE: " << entry->name() << std::endl;
						break;
					default:
						std::cout << "* OTHER: " << entry->name() << std::endl;
						break;
					}
				}
				*/
			}

			ct++;

			if (ct > 2)
				break;
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