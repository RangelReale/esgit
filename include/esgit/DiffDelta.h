#pragma once

#include "esgit/DiffFile.h"

#include <git2.h>

#include <memory>

namespace esgit {

/**
 * @brief Wrapper class for git_diff_delta.
 *
 * @ingroup LibQGit2
 * @{
 */
class DiffDelta
{
public:
	typedef std::shared_ptr<DiffDelta> Ptr;

    DiffDelta(const git_diff_delta *d);

	~DiffDelta();

    enum Type {
        Unknown = GIT_DELTA_UNMODIFIED - 1,  ///< unknown type
        Unmodified = GIT_DELTA_UNMODIFIED,   ///< no changes
        Added = GIT_DELTA_ADDED,             ///< entry does not exist in old version
        Deleted = GIT_DELTA_DELETED,         ///< entry does not exist in new version
        Modified = GIT_DELTA_MODIFIED,       ///< entry content changed between old and new
        Renamed = GIT_DELTA_RENAMED,         ///< entry was renamed between old and new
        Copied = GIT_DELTA_COPIED,           ///< entry was copied from another old entry
        Ignored = GIT_DELTA_IGNORED,         ///< entry is ignored item in workdir
        Untracked = GIT_DELTA_UNTRACKED,     ///< entry is untracked item in workdir
        Typechange = GIT_DELTA_TYPECHANGE,   ///< type of entry changed between old and new
		Unreadable = GIT_DELTA_UNREADABLE,   ///< entry is unreadable
		Conflicted = GIT_DELTA_CONFLICTED	 ///< entry in the index is conflicted
	};

    /**
     * Gets the type of this delta.
     */
    Type type() const;

    /**
     * Returns the information of the file on the "old" side of the diff.
     */
    DiffFile::Ptr oldFile() const;

    /**
     * Returns the information of the file on the "new" side of the diff.
     */
    DiffFile::Ptr newFile() const;
private:
	class Private;
	std::unique_ptr<Private> _pimpl;
};


}
