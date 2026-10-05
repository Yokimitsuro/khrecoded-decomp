#include "nitro/types.h"

typedef struct ModeArchiveContext {
    u8 pad_000[0x140];
    u8 archive[0x648];
    u8 archiveExtra[0x4c];
    void *workBuffer;
    u8 pad_7d8[0x184];
    u8 workArea[0x3584];
    void *container;
    u8 pad_3ee4[8];
    u8 resourceName[0x10];
    int loadedMode;
} ModeArchiveContext;

extern ModeArchiveContext *data_ov001_020a0500;
extern char sOv001_EvEVW0FormatDP2_0209f300[];
extern signed char func_ov001_02068084(void);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern int findSharedResourceByName(void *table, void *name);
extern int RoundAndInitArchive(void *record, int flags, int flag, void *extra);
extern void SetLoaderCallbacks(void *context, void *writeHandler, void *readHandler);
extern void WriteSessionPackedBits();
extern void ReadSessionPackedBits();

void ReloadModeMessageArchive(void)
{
    ModeArchiveContext *context = data_ov001_020a0500;
    char name[16];
    int resource;

    if (context->container == NULL || context->loadedMode != func_ov001_02068084()) {
        OS_SPrintf(name, sOv001_EvEVW0FormatDP2_0209f300, func_ov001_02068084() + 1);
        context->container = Msg_OpenContainerAndReadHeader(name, 0xd, FALSE);
        context->loadedMode = func_ov001_02068084();
    }
    context->workBuffer = context->workArea;
    resource = findSharedResourceByName(context->container, context->resourceName);
    RoundAndInitArchive(context->archive,
                                 (((u32)context->container + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (resource & 0x1ff),
                                 0, context->archiveExtra);
    SetLoaderCallbacks(context->archive, WriteSessionPackedBits, ReadSessionPackedBits);
}
