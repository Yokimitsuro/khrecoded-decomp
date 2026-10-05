#include "nitro/types.h"

typedef struct MeshNamedEntry MeshNamedEntry;

typedef struct LinkData {
    u8 pad_00[0x80];
    u8 meshEntryIds[4];
} LinkData;

typedef struct LinkState {
    u32 unk_00;
    LinkData *data;
    u8 pad_08[0x8];
    int unk_10;
    u8 pad_14[0xc4 - 0x14];
    int mode;
} LinkState;

typedef struct Actor {
    u8 pad_0000[0x274];
    LinkState link;
} Actor;

extern MeshNamedEntry *GetWorldMeshNamedEntry(int index);
extern BOOL func_ov001_020681e8(MeshNamedEntry *entry, u32 kind);

void ProbeLinkedMeshEntries(Actor *actor)
{
    LinkState *link = &actor->link;
    int i;

    if (link->data != NULL && link->mode == 2 && link->unk_10 == 0) {
        for (i = 0; i < 4; i++) {
            MeshNamedEntry *entry = GetWorldMeshNamedEntry(link->data->meshEntryIds[i]);
            if (entry != NULL) {
                func_ov001_020681e8(entry, 5);
            }
        }
    }
}
