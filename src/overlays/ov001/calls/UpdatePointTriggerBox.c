#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TriggerBox {
    VecFx32 min;
    VecFx32 max;
    int value;
    u8 pad_1c[0x8];
} TriggerBox;

typedef struct PointItem {
    u8 pad_00[0x6];
    s8 flagIndex;
    u8 pad_07[0x15];
    int value;
} PointItem;

typedef struct PointTable {
    u8 pad_00[0x8];
    PointItem *items[1];
} PointTable;

typedef struct SceneContext {
    PointTable *table;
    u8 pad_04[0x10];
    TriggerBox *boxes;
    u8 pad_18[0x10a4];
    int defaultValue;
} SceneContext;

typedef struct PointTrigger {
    u8 pad_00;
    u8 itemId;
    u8 pad_02[0x4];
    s16 margin;
} PointTrigger;

extern SceneContext *data_ov001_020a048c;
extern void *GetActorRegistry(void);
extern int func_ov001_02067ed4(void);
extern BOOL ComputeNamedPointBounds(int setIndex, int recordIndex, VecFx32 *outMin, VecFx32 *outMax);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern BOOL func_ov001_02067f08(int itemId, int *outIndex);
extern BOOL func_ov001_020645c8(u32 value);

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void UpdatePointTriggerBox(PointTrigger *trigger, int index)
{
    SceneContext *ctx = data_ov001_020a048c;
    VecFx32 max;
    VecFx32 min;
    VecFx32 center;
    VecFx32 half;
    int itemIndex;
    TriggerBox *box;
    PointItem *item;

    GetActorRegistry();
    if (ComputeNamedPointBounds(func_ov001_02067ed4(), index, &min, &max)) {
        VEC_Subtract(&max, &min, &half);
        half.x >>= 1;
        half.y >>= 1;
        half.z >>= 1;
        VEC_Add(&min, &half, &center);
        box = &ctx->boxes[index];
        SetVec(&box->min, center.x - (half.x + trigger->margin), center.y - half.y, center.z - (half.z + trigger->margin));
        SetVec(&box->max, center.x + (half.x + trigger->margin), center.y + half.y, center.z + (half.z + trigger->margin));
        if (func_ov001_02067f08(trigger->itemId, &itemIndex)) {
            item = data_ov001_020a048c->table->items[itemIndex];
            if (item->flagIndex >= 0 && func_ov001_020645c8(item->flagIndex + 0x10d0)) {
                box->value = item->value;
                return;
            }
            box->value = ctx->defaultValue;
        }
    }
}
