#include "nitro/types.h"

typedef struct ZoneData {
    u8 pad00[0x80];
    u8 meshIds[4];
} ZoneData;

typedef struct ZoneObject {
    ZoneData *data;
    s32 mode;
} ZoneObject;

extern void *GetWorldMeshNamedEntry(int index);
extern BOOL func_ov001_020681e8(void *entry, u32 kind);

BOOL AreZoneMeshesClear(ZoneObject *zone)
{
    BOOL clear = TRUE;
    int i;

    if (zone->mode == 2) {
        for (i = 0; i < 4; i++) {
            void *entry = GetWorldMeshNamedEntry(zone->data->meshIds[i]);
            if (entry != NULL && func_ov001_020681e8(entry, 2)) {
                clear = FALSE;
                break;
            }
        }
    }
    return clear;
}
