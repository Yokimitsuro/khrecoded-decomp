#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x2c];
    u16 resultType;
    u8 pad_2e[2];
    s32 result;
} ScriptContext;

typedef struct {
    u8 pad_00[0x16];
    u16 motionId;
} ScriptOwner;

typedef struct SlotTable SlotTable;

extern ScriptOwner *data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *value);
extern SlotTable *GetStageMotionRecord(u32 id);
extern int SlotTable_FindNearestFree(SlotTable *table, fx32 height, int heightSign, int distanceSign);

int ScriptOp_FindNearestFreeSlot(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *height = ResolveTaggedValueRef(context, args + 1);
    SlotTable *table;

    if (data_ov021_020b56c4 == NULL) {
        return 0;
    }
    table = GetStageMotionRecord(data_ov021_020b56c4->motionId);
    if (table == NULL) {
        return 0;
    }
    context->resultType = 1;
    context->result = SlotTable_FindNearestFree(table, TaggedValueToFixed(height), -1, 1);
    return 0;
}
