#pragma once

#include <esgit/DiffDelta.h>
#include <esgit/Buffer.h>

#include <git2.h>

#include <memory>

namespace esgit {

/**
 * This class represents a diff.
 */
class Diff
{
public:
	typedef std::shared_ptr<Diff> Ptr;

	enum Format {
		Patch = GIT_DIFF_FORMAT_PATCH, /**< full git diff */
		Header = GIT_DIFF_FORMAT_PATCH_HEADER, /**< just the file headers of patch */
		Raw = GIT_DIFF_FORMAT_RAW, /**< like git diff --raw */
		NameOnly = GIT_DIFF_FORMAT_NAME_ONLY, /**< like git diff --name-only */
		NameStatus = GIT_DIFF_FORMAT_NAME_STATUS /**< like git diff --name-status */
	};

    Diff(git_diff *diff);

	~Diff();

    /**
     * @brief Get the number of \c DiffDelta objects in this \c Diff.
     */
    size_t numDeltas() const;

    /**
     * @brief Get the \c DiffDelta for the specified index.
     *
     * If the given \a index is not on a valid range then a \c NULL \c DiffDelta
     * object is returned.
     *
     * @param index an index from the interval 0 <= index < numDeltas().
     * @return The \c DiffDelta member.
     */
    DiffDelta::Ptr delta(size_t index) const;

	Buffer::Ptr format(Format fmt);

	git_diff* data() const;
	const git_diff* constData() const;
public:
	class Private;
	std::unique_ptr<Private> _pimpl;
};

}
