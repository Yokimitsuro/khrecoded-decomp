#include "nitro/types.h"

typedef struct FieldNode {
    u8 pad_00[8];
    u16 flags;
} FieldNode;

typedef struct FieldObject {
    u8 pad_00[8];
    FieldNode *node;
    u8 pad_0C[0x24];
    u16 statusFlags;
    u8 slot;
    u8 pad_33[0x14];
    s8 idleAnim;
    u8 pad_48[2];
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
    u8 pad_4C[4];
    s32 kind : 16;
    s32 subKind : 12;
    s32 bit28 : 1;
    s32 hitsLeft : 3;
    u8 pad_54[0x14];
    s32 timer;
} FieldObject;

extern u8 *ActorRegistry_GetEntityByIndex(int slot);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern void selectJointAnimationBlend(void *anim, u16 trackIndex, void *blendTable, short blendIndex);
extern void func_ov017_020a3c98(FieldObject *object, int arg);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void CacheEntry_SetActive(FieldObject *object, BOOL active);
extern u16 GetSavedStateValue(FieldObject *object);
extern void SetSavedStateValue(FieldObject *object, u16 value);
extern void TransitionRecordSlot(int index);

void ResetFieldObjectToIdle(FieldObject *object)
{
    u8 *actor;

    object->state = 0;
    actor = ActorRegistry_GetEntityByIndex(object->slot);
    RebindAnimTracks(actor + 4, object->idleAnim, 0);
    Flags16_ClearBit1(actor + 4);
    selectJointAnimationBlend(actor + 4, 2, actor + 0xdc, -1);
    if (object->flags & 2) {
        func_ov017_020a3c98(object, 0);
    } else {
        ActorSlot_SetFlag8ByIndex(object->slot, TRUE);
        CacheEntry_SetActive(object, TRUE);
    }
    SetSavedStateValue(object, GetSavedStateValue(object) & ~1);
    if (!(object->node->flags & 0x100)) {
        TransitionRecordSlot(object->slot);
    }
    object->hitsLeft = 1;
    object->timer = 0;
    object->bit28 = 1;
    object->statusFlags |= 0x10;
}
