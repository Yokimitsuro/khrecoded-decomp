#include "nitro/types.h"

typedef struct MeshRoomData {
    s8 unk_00;
    s8 area;
    s8 room;
    s8 variant;
} MeshRoomData;

typedef struct MeshNamedEntry {
    u8 pad_00[0xc];
    u8 visible;
    u8 pad_0d[3];
    MeshRoomData *data;
} MeshNamedEntry;

typedef struct DoorObject {
    u8 pad_00[0x1c];
    u8 *roomId;
    u8 area;
    u8 variant;
    u16 state;
} DoorObject;

extern const char sOv001_FormatSFormat02d_0209ea90[];
extern const char sOv001_ColWall_0209ea84[];
extern const char sOv001_Gate_0209ea98[];
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int strlen(const char *str);
extern void ApplyToNamedCollisionFaces(const char *name, int nameLength, BOOL enable);
extern MeshNamedEntry *FindWorldMeshEntryByName(const char *name);
extern void SetWorldMeshEntryDataByName(const char *name, const void *src, u32 size);

void SyncDoorMeshState(DoorObject *door)
{
    u32 room;
    u32 openState;
    MeshNamedEntry *entry;
    MeshRoomData *current;
    char meshName[8];
    MeshRoomData data;
    char collisionName[16];

    room = *door->roomId;
    openState = door->state & 3;
    OS_SPrintf(collisionName, sOv001_FormatSFormat02d_0209ea90, sOv001_ColWall_0209ea84, room);
    ApplyToNamedCollisionFaces(collisionName, strlen(collisionName), openState == 0);
    OS_SPrintf(meshName, sOv001_FormatSFormat02d_0209ea90, sOv001_Gate_0209ea98, room);
    if (openState == 0) {
        entry = FindWorldMeshEntryByName(meshName);
        if (entry != NULL) {
            entry->visible = 0;
        }
        return;
    }
    entry = FindWorldMeshEntryByName(meshName);
    if (entry == NULL) {
        return;
    }
    entry->visible = 1;
    current = entry->data;
    if (current != NULL && current->area == door->area && current->room == room && current->variant == door->variant) {
        return;
    }
    data.area = door->area;
    data.room = room;
    data.variant = door->variant;
    data.unk_00 = 0;
    SetWorldMeshEntryDataByName(meshName, &data, sizeof(MeshRoomData));
}
