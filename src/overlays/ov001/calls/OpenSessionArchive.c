#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x648];
    u8 workArea[0x81c - 0x648];
    u8 *resourceTable;
} SessionArchive;

typedef struct {
    u8 pad_0000[0x1f10];
    SessionArchive archive;
} Session;

extern Session *data_ov001_020a0480;
extern void FormatSessionNumber(int number, char *buffer);
extern u32 findSharedResourceByName(u8 *table, char *name);
extern int RoundAndInitArchive(SessionArchive *archive, u32 flags, int flag, void *extra);
extern void SetLoaderCallbacks(SessionArchive *archive, void *writeHandler, void *readHandler);
extern void WriteSessionPackedBits(void);
extern void ReadSessionPackedBits(void);

void OpenSessionArchive(int number, int flag)
{
    SessionArchive *archive = &data_ov001_020a0480->archive;
    char name[12];
    u32 index;

    FormatSessionNumber(number, name);
    index = findSharedResourceByName(archive->resourceTable, name);
    RoundAndInitArchive(archive, ((((u32)archive->resourceTable + 0x8000) & 0xfffffc) << 7 | 0x80000000) | (index & 0x1ff), flag, archive->workArea);
    SetLoaderCallbacks(archive, WriteSessionPackedBits, ReadSessionPackedBits);
}
