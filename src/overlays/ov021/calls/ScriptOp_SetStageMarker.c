#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageMarker {
    u32 flags;
    VecFx32 position;
    fx32 radius;
    u8 pad14[0xc];
} StageMarker;

typedef struct StageManager {
    u8 pad0[0x18e78];
    StageMarker markers[1];
} StageManager;

typedef struct TaggedValue {
    s16 tag;
    s16 pad2;
    int value;
} TaggedValue;

typedef struct MarkerOperands {
    u8 index[8];
    u8 pad8[4];
    u32 flags;
    u8 position[0x18];
    u8 radius[8];
} MarkerOperands;

extern TaggedValue *ResolveTaggedValueRef(void *context, void *value);
extern s32 TaggedValueToFixed(void *tagged);
extern StageManager *func_ov001_0209c3e8(void);
extern void ResolveOffsetPosition(void *context, u32 flags, void *operands, VecFx32 *out, int *extra);

int ScriptOp_SetStageMarker(void *context, MarkerOperands *operands)
{
    TaggedValue *index = ResolveTaggedValueRef(context, operands->index);
    void *radius = ResolveTaggedValueRef(context, operands->radius);
    int extra = 0;
    StageManager *stage = func_ov001_0209c3e8();
    VecFx32 position;

    ResolveOffsetPosition(context, operands->flags & ~0x40, operands->position, &position, &extra);
    stage->markers[index->value].flags = operands->flags;
    stage->markers[index->value].position = position;
    stage->markers[index->value].radius = TaggedValueToFixed(radius);
    return 0;
}
