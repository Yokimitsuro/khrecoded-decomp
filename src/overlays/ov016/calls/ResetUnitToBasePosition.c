#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorNode {
    u32 flags_000;
    u16 flags_004;
} ActorNode;

typedef struct Unit {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x05];
    VecFx32 position;
    u8 pad_44[0x03];
    s8 animBlend;
    u8 pad_48[0x28];
    u16 flag70_0 : 1;
    u16 isMoving : 1;
    u16 flag70_rest : 14;
    u8 pad_72[0x05];
    u8 action;
    u8 pad_78[0x20];
    s32 unk_98;
    s32 unk_9C;
    VecFx32 basePosition;
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x09];
    u8 pad_BD_lo : 4;
    u8 state : 4;
    u8 pad_BE[0x06];
    s32 unk_C4;
    s32 unk_C8;
    VecFx32 velocity;
    u32 flags_D8;
    u8 data_DC[0x0A];
    u16 field_E6_a : 14;
    u16 field_E6_b : 1;
    u16 field_E6_c : 1;
    u8 pad_E8[0x04];
    union {
        u32 raw;
        struct {
            u16 count : 15;
            u16 flag : 1;
        } bits;
    } timer;
    s32 unk_F0;
    s32 unk_F4;
} Unit;

extern const VecFx32 data_0205344c;
extern void *MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern ActorNode *ActorRegistry_GetEntityByIndex(u32 id);
extern void RebindAnimTracks(u16 *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(u16 *anim);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void CacheEntry_SetActive(Unit *unit, BOOL active);
extern void func_ov016_020a6a1c(Unit *unit);
extern void SetFieldObjectHidden(Unit *unit, int arg);
extern void SaveFieldUnitMode(Unit *unit);
extern void InstallFieldObjectHitCallbacks(Unit *unit);

void ResetUnitToBasePosition(Unit *unit)
{
    ActorNode *actor;
    BOOL keepMotion = TRUE;

    if (unit->state != 2 && unit->state != 4) {
        keepMotion = FALSE;
    }
    unit->position = unit->basePosition;
    switch (unit->action) {
    case 3:
        unit->flags_D8 &= ~1;
        break;
    case 5:
        unit->velocity.x = 0;
        break;
    case 7:
        unit->velocity = data_0205344c;
        break;
    case 11:
        unit->velocity.x = 0;
        unit->velocity.y = 0;
        unit->flags_D8 = (unit->flags_D8 & ~0xff) | 0xff;
        MIi_CpuClearFast(0, unit->data_DC, 0x10);
        break;
    case 9:
    case 12:
    case 13:
    case 14:
    case 15:
        unit->velocity = data_0205344c;
        unit->field_E6_a = 0;
        unit->field_E6_b = 0;
        unit->field_E6_c = 0;
        break;
    case 16:
        break;
    }
    if (unit->state == 1) {
        unit->timer.raw = 0;
    } else if (unit->state < 5 && keepMotion) {
        unit->timer.bits.count = 0;
        unit->unk_F0 = 0;
        unit->unk_F4 = 0;
    }
    unit->unk_C4 = 0;
    unit->unk_C8 = 0;
    unit->unk_98 = 0;
    unit->unk_9C = 0;
    unit->isMoving = 0;
    unit->unk_AC = unit->unk_B0;
    func_ov016_020a6a1c(unit);
    actor = ActorRegistry_GetEntityByIndex(unit->actorId);
    RebindAnimTracks(&actor->flags_004, unit->animBlend, 0);
    Flags16_ClearBit1(&actor->flags_004);
    ActorSlot_SetFlag8ByIndex(unit->actorId, TRUE);
    CacheEntry_SetActive(unit, TRUE);
    SetFieldObjectHidden(unit, 0);
    SaveFieldUnitMode(unit);
    InstallFieldObjectHitCallbacks(unit);
}
