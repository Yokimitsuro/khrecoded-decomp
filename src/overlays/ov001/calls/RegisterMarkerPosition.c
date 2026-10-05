#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 active;
    u16 pad_02;
    u16 kind;
    u16 id;
    VecFx32 position;
    u8 pad_14[0x28 - 0x14];
} MarkerEntry;

typedef struct {
    u32 flags;
    u8 pad_00004[0x18814 - 0x4];
    MarkerEntry markers[37];
    u8 pad_18ddc[0x18df2 - 0x18ddc];
    u16 markerCount;
} MarkerManager;

extern MarkerManager *data_ov001_020a0528;

extern BOOL func_ov001_0208724c(u32 kind, u32 id);

void RegisterMarkerPosition(u16 kind, u16 id, VecFx32 *position) {
    MarkerEntry *entry = NULL;
    int i;

    if (data_ov001_020a0528->flags & 0x10000) {
        return;
    }
    if (func_ov001_0208724c(kind, id)) {
        for (i = 0; i < data_ov001_020a0528->markerCount; i++) {
            MarkerEntry *marker = data_ov001_020a0528->markers + i;
            if (marker->id == id + 1) {
                entry = marker;
                break;
            }
        }
        if (entry == NULL) {
            entry = &data_ov001_020a0528->markers[data_ov001_020a0528->markerCount];
            data_ov001_020a0528->markerCount++;
        }
        entry->kind = kind;
        entry->id = id + 1;
        entry->position = *position;
        entry->active = 1;
    }
}
