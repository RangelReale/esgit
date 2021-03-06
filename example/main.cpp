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


				//std::cout << "DIFF:" << std::endl;
				//std::cout << diff->format(esgit::Diff::Format_Patch)->asString() << std::endl;

				for (int i = 0; i < diff->numDeltas(); i++)
				{
					esgit::DiffDelta::Ptr delta = diff->delta(i);
					esgit::Patch::Ptr patch = diff->patch(i);

					std::cout << "DIFF DELTA: " << delta->newFile()->path() << std::endl;

					esgit::Object::Ptr deltaobj = repo->lookupAny(delta->newFile()->oid());
					if (deltaobj)
					{
						switch (deltaobj->type())
						{
						case esgit::Object::BlobType:
						{
							std::cout << "* FILE: " << std::endl;

							//auto blob = esgit::Blob::fromObject(deltaobj);
							//std::cout << blob->content();
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

					for (int h = 0; h < patch->numHunks(); h++)
					{
						esgit::DiffHunk::Ptr hunk(patch->hunk(h));

						std::cout << "HUNK: " << hunk->numLines() << " lines" << std::endl;

						for (int hl = 0; hl < hunk->numLines(); hl++)
						{
							esgit::DiffLine::Ptr line(hunk->line(hl));

							std::cout << "LINE: " << hl << std::endl;
							std::cout << std::string(line->data()->content, line->data()->content_len);
						}
					}

					//std::cout << patch->format()->asString() << std::endl;
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