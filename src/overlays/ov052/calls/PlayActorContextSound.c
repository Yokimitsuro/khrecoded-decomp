#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[4];
    s8 *partyInfo;
    u8 pad_08[8];
    s8 *enemyInfo;
    u8 pad_14[0xbc - 0x14];
    fx32 baseHeight;
    u8 pad_c0[4];
    int ownerKind;
} OwnerState;

typedef struct {
    u8 pad_0000[0x274];
    OwnerState owner;
    u8 pad_033c[0x9b8 - 0x33c];
    u32 soundKind;
    u8 pad_09bc[4];
    int stageType;
} Actor;

extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern s32 func_ov001_02063a38(void);
extern int func_ov001_020644b0(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov001_02067ed4(void);
extern s8 func_ov001_02068084(void);
extern int LookupKindTableValue(u32 kind, int index);
extern BOOL AnySubObjectFlagsActive(Actor *actor);

u32 PlayActorContextSound(Actor *actor, int sound, int arg, int flags)
{
    u32 result = 0;
    u32 soundFlags = (u16)flags;

    switch (sound) {
    case 4:
    case 0x15:
    case 0x23: {
        OwnerState *owner = &actor->owner;
        VecFx32 *pos = func_ov052_020ceb74(actor);
        int index = -1;
        sound = -1;
        if (!func_ov001_020645c8(0x3627) && pos->y - owner->baseHeight < 0x3000) {
            switch (owner->ownerKind) {
            case 1:
                if (owner->enemyInfo != NULL) {
                    index = owner->enemyInfo[0x13];
                }
                break;
            case 2:
                if (owner->partyInfo != NULL) {
                    index = owner->partyInfo[0x83];
                }
                break;
            }
        }
        if (index >= 0) {
            sound = LookupKindTableValue(actor->soundKind, index);
        }
        break;
    }
    case 8:
        sound = 9;
        if (actor->stageType != 0x10) {
            sound = -1;
        } else {
            BOOL special = func_ov001_020644b0() == 900 ? TRUE : FALSE;
            if (special) {
                sound = 0x10;
            } else {
                int mode = func_ov001_02067ed4();
                switch (func_ov001_02068084()) {
                case 1:
                    switch (mode) {
                    case 2:
                        sound = 10;
                        break;
                    case 1:
                    case 3:
                    case 4:
                        sound = 4;
                        break;
                    }
                    break;
                case 2:
                    if (mode == 8) {
                        sound = 0xf;
                    }
                    break;
                }
            }
        }
        break;
    }
    if (actor->soundKind == 0 && arg == 0x1f && !AnySubObjectFlagsActive(actor)) {
        sound = -1;
        arg = -1;
    }
    if (sound >= 0 && arg >= 0) {
        if (func_ov001_02063a38() != 4 && actor->soundKind == 0) {
            soundFlags |= 5;
        }
        result = SpawnSoundSlot(sound, arg, func_ov052_020ceb74(actor), soundFlags);
    }
    return result;
}
