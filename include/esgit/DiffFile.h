#pragma once

#include <git2.h>

#include <string>
#include <memory>

namespace esgit {

/**
 * @brief Wrapper class for git_diff_file.
 *
 * @ingroup LibQGit2
 * @{
 */
class DiffFile
{
public:
	typedef std::shared_ptr<DiffFile> Ptr;

    DiffFile(git_diff_file *diff);

	~DiffFile();

    /**
     * Returns the path of the file if it is known. Otherwise returns an empty string.
     */
    std::string path() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}
