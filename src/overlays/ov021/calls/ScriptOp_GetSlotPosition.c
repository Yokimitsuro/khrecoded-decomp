#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 vector;
} ScriptContext;

typedef struct {
    u8 pad_00[0x16];
    u16 motionId;
} ScriptOwner;

typedef struct {
    u8 pad_000[0x2c0];
    VecFx32 position;
} PlayerActor;

typedef struct {
    ScriptOwner *owner;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

typedef struct {
    u32 unk_00;
    VecFx32 position;
} SlotEntry;

typedef struct SlotTable SlotTable;

extern ScriptGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt(TaggedValue *value);
extern SlotTable *GetStageMotionRecord(u32 id);
extern SlotEntry *SlotTable_GetEntry(SlotTable *table, int index);

int ScriptOp_GetSlotPosition(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *index = ResolveTaggedValueRef(context, args + 1);
    PlayerActor *player = data_ov021_020b56c4.player;
    SlotTable *table = GetStageMotionRecord(data_ov021_020b56c4.owner->motionId);
    SlotEntry *entry = SlotTable_GetEntry(table, TaggedValueToInt(index));

    if (entry != NULL) {
        context->vector = entry->position;
    } else if (player != NULL) {
        context->vector = player->position;
    }
    return 0;
}

