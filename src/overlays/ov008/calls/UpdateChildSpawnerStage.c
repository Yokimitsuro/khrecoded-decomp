#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x4];
    u16 anim;
} AnimBody;

typedef struct {
    u8 pad_00[0x10];
    AnimBody body;
} SpawnerEntry;

typedef struct FieldObject {
    u8 pad_00[0xc];
    SpawnerEntry *entry;
    u8 pad_10[0x43];
    s8 stage;
    u8 pad_54[0x10];
    fx32 frame;
} FieldObject;

extern const s16 data_ov008_020a1400[];
extern BOOL AdvanceAnimFrame_02080a60(void *anim, fx32 step, BOOL loop, fx32 length, fx32 *frame);
extern void FieldObject_SetSavedValue(FieldObject *object, u32 value);
extern u16 FieldObject_GetSavedValue(FieldObject *object);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_SetBit1(void *anim);

int UpdateChildSpawnerStage(FieldObject *object)
{
    AnimBody *body = &object->entry->body;
    s16 length = data_ov008_020a1400[object->stage];

    if (length == 1) {
        AdvanceAnimFrame_02080a60(&body->anim, 0x1000, TRUE, length << 12, &object->frame);
    } else if (!AdvanceAnimFrame_02080a60(&body->anim, 0x1000, FALSE, length << 12, &object->frame)) {
        object->stage++;
        FieldObject_SetSavedValue(object, object->stage);
        RebindAnimTracks(&object->entry->body.anim, object->stage, 0);
        object->frame = 0;
        Flags16_SetBit1(&object->entry->body.anim);
    }
    if (object->stage != FieldObject_GetSavedValue(object)) {
        object->stage = FieldObject_GetSavedValue(object);
        RebindAnimTracks(&object->entry->body.anim, object->stage, 0);
        object->frame = 0;
        Flags16_SetBit1(&object->entry->body.anim);
    }
    return 0;
}
