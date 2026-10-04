#include "libs/nitro/fs/fs_string_internal.h"


typedef struct FSGlobalState {
    FSArchive *archiveList;
    FSDirPos currentDirectory;
} FSGlobalState;

#define fsi_archive_state (*(FSGlobalState *)&arc_list)

extern int FSi_DecrementSjisPositionToSlash(const char *text, int position);
extern int FSi_TrimSjisTrailingSlash(char *text);

FSArchive *FS_NormalizePath(const char *path, u32 *baseDirectoryId,
                            char *relativePath)
{
    FSArchive *currentArchive = fsi_archive_state.currentDirectory.archive;
    FSArchive *archive = 0;
    int pathLength = 0;
    int pathMaximum = 260;
    BOOL stickyFailure = 0;

    if (currentArchive == 0) {
        fsi_archive_state.currentDirectory.archive = arc_list;
        fsi_archive_state.currentDirectory.ownId = 0;
        fsi_archive_state.currentDirectory.position = 0;
        fsi_archive_state.currentDirectory.index = 0;
        current_dir_path[0] = '\0';
    }

    if (FSi_IsSlash((u8)*path)) {
        archive = fsi_archive_state.currentDirectory.archive;
        ++path;
        if (baseDirectoryId != 0) {
            *baseDirectoryId = 0;
        }
    } else {
        int position;

        for (position = 0;;
             position = FSi_IncrementSjisPosition(path, position)) {
            u32 character = (u8)path[position];

            if (character == 0 || FSi_IsSlash(character)) {
                archive = fsi_archive_state.currentDirectory.archive;
                if (baseDirectoryId != 0) {
                    *baseDirectoryId =
                        fsi_archive_state.currentDirectory.ownId;
                }
                if (relativePath != 0) {
                    if (fsi_archive_state.currentDirectory.ownId == 0 &&
                        current_dir_path[0] != '\0') {
                        pathLength += FSi_CopySafeString(
                            &relativePath[pathLength], pathMaximum - pathLength,
                            current_dir_path, 260, &stickyFailure);
                        pathLength += FSi_CopySafeString(
                            &relativePath[pathLength], pathMaximum - pathLength,
                            "/", 1, &stickyFailure);
                    }
                }
                break;
            } else if (character == ':') {
                archive = FS_FindArchive(path, position);
                path += position + 1;
                if (FSi_IsSlash((u8)*path)) {
                    ++path;
                }
                if (baseDirectoryId != 0) {
                    *baseDirectoryId = 0;
                }
                break;
            }
        }
    }

    if (relativePath != 0) {
        int componentLength = 0;

        while (!stickyFailure) {
            char character = path[componentLength];

            if (character != '\0' && !FSi_IsSlash((u8)character)) {
                componentLength +=
                    STD_IsSjisCharacter(&path[componentLength]) ? 2 : 1;
            } else {
                if (componentLength == 0) {
                } else if (componentLength == 1 && path[0] == '.') {
                } else if (componentLength == 2 && path[0] == '.' &&
                           path[1] == '.') {
                    if (pathLength > 0) {
                        --pathLength;
                    }
                    pathLength = FSi_DecrementSjisPositionToSlash(
                                     relativePath, pathLength) +
                                 1;
                } else {
                    pathLength += FSi_CopySafeString(
                        &relativePath[pathLength], pathMaximum - pathLength,
                        path, componentLength, &stickyFailure);
                    if (character != '\0') {
                        pathLength += FSi_CopySafeString(
                            &relativePath[pathLength],
                            pathMaximum - pathLength, "/", 1,
                            &stickyFailure);
                    }
                }
                if (character == '\0') {
                    break;
                }
                path += componentLength + 1;
                componentLength = 0;
            }
        }
        relativePath[pathLength] = '\0';
        pathLength = FSi_TrimSjisTrailingSlash(relativePath);
    }
    return stickyFailure ? 0 : archive;
}