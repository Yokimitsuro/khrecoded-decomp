#include "nitro/types.h"

typedef struct EffectSlotData {
    u8 pad_00[0x54];
    u32 recordA;
    s32 handleA;
    u32 recordB;
    s32 handleB;
    s16 resourceA;
    s16 resourceB;
    u8 pad_68[0x16];
    u8 flags;
} EffectSlotData;

typedef struct EffectSlot {
    u8 pad_00[8];
    EffectSlotData *data;
} EffectSlot;

extern u32 func_ov001_0207f0e0(s32 resource, u32 *record, u32 mode);
extern s32 func_ov001_0207f0d0(s32 resource, u32 mode);

void AcquireEffectRecordPair(EffectSlot *slot)
{
    EffectSlotData *data = slot->data;

    if (data->resourceA >= 0) {
        func_ov001_0207f0e0(data->resourceA, &data->recordA, 3);
        if (!(data->flags & 1)) {
            data->handleA = func_ov001_0207f0d0(data->resourceA, 3);
        }
    }
    if (data->resourceB >= 0) {
        func_ov001_0207f0e0(data->resourceB, &data->recordB, 3);
        if (!(data->flags & 1)) {
            data->handleB = func_ov001_0207f0d0(data->resourceB, 3);
        }
    }
}
