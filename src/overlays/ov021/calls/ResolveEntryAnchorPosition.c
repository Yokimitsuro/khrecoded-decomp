#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00;
    s8 actorId;
    s8 anchorMode;
    u8 pad_03;
    u16 flags;
    u8 pad_06[0xA6];
    VecFx32 fixedPosition;
    u8 pad_b8[0x64];
    VecFx32 localOffset;
} AnchorEntry;

extern const VecFx32 data_0205344c;
extern const s16 data_02053580[];
extern u16 GetBiasAdjustedField(int actorId);
extern VecFx32 *func_ov001_0206dc60(int actorId);
extern VecFx32 *func_ov001_0206dc4c(int actorId);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void ResolveEntryAnchorPosition(VecFx32 *out, AnchorEntry *entry)
{
    VecFx32 position = data_0205344c;
    MtxFx33 rotation;
    VecFx32 rotatedOffset;

    switch (entry->anchorMode) {
    case 0:
        position = entry->fixedPosition;
        break;
    case 1: {
        int angle = GetBiasAdjustedField(entry->actorId);
        VecFx32 *base;
        int index;

        if (entry->flags & 1) {
            base = func_ov001_0206dc60(entry->actorId);
        } else {
            base = func_ov001_0206dc4c(entry->actorId);
        }
        index = angle >> 4;
        MTX_RotY33_(&rotation, -data_02053580[index], -data_02053580[(0x400 - index) & 0xfff]);
        MTX_MultVec33(&entry->localOffset, &rotation, &rotatedOffset);
        VEC_Add(base, &rotatedOffset, &position);
        break;
    }
    case 2:
        position = *func_ov001_0206dc60(entry->actorId);
        break;
    }
    *out = position;
}
