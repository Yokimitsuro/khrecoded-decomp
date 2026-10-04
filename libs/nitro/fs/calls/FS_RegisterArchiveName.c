#include "libs/nitro/fs/fs_internal.h"

char current_dir_path[260];
char FSiLongNameTable[16][16];
FSDirPos current_dir_pos;
FSArchive *arc_list;
extern int STD_CopyLString(char *destination, const char *source, int length);
extern void OS_Terminate(void);

BOOL FS_RegisterArchiveName(FSArchive *archive, const char *name,
                            u32 nameLength)
{
    BOOL result = 0;
    OSIntrMode interruptState = OS_DisableInterrupts();

    if (FS_FindArchive(name, (int)nameLength) == 0) {
        FSArchive **link;

        for (link = &arc_list; *link != 0; link = &(*link)->next) {
        }
        *link = archive;

        if (nameLength <= 3) {
            archive->name.packed = 0;
            (void)STD_CopyLString(archive->name.shortName, name,
                                  (int)(nameLength + 1));
        } else if (nameLength <= 15) {
            int index;

            for (index = 0;; ++index) {
                if (index >= 16) {
                    OS_Terminate();
                } else if (FSiLongNameTable[index][0] == '\0') {
                    (void)STD_CopyLString(FSiLongNameTable[index], name,
                                          (int)(nameLength + 1));
                    archive->name.packed = (u32)FSiLongNameTable[index];
                    break;
                }
            }
        } else {
            OS_Terminate();
        }
        archive->flags |= FS_ARCHIVE_FLAG_REGISTER;
        result = 1;
    }
    (void)OS_RestoreInterrupts(interruptState);
    return result;
}