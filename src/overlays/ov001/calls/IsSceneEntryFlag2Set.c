#include "nitro/types.h"

typedef struct SceneEntry {
    u8 pad_00[0x14];
    u8 flags;
    u8 pad_15[0x108 - 0x15];
} SceneEntry;

typedef struct SceneEntryTable {
    u8 header[0x108];
    SceneEntry entries[1];
} SceneEntryTable;

extern SceneEntryTable *data_ov001_020a048c;

int IsSceneEntryFlag2Set(int index)
{
    return data_ov001_020a048c->entries[index].flags & 4;
}


