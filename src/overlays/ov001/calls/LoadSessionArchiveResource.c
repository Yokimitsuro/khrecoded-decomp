#include "nitro/types.h"

typedef struct SessionScript {
    u8 pad_000[0x81c];
    u8 *archive;
    u8 pad_820[0xc];
    void *resource;
} SessionScript;

typedef struct Session {
    u8 pad_0000[0x1f10];
    SessionScript script;
} Session;

extern Session *data_ov001_020a0480;
extern char sOv001_Fz_0209e6fc[];
extern int findSharedResourceByName(unsigned char *table, void *name);
extern void *Archive_LoadFile(u32 fileId, u32 heapId);

void LoadSessionArchiveResource(void) {
    SessionScript *script = &data_ov001_020a0480->script;
    int index = findSharedResourceByName(script->archive, sOv001_Fz_0209e6fc);
    script->resource = Archive_LoadFile(
        ((((u32)(script->archive + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (index & 0x1ff), 2);
}
