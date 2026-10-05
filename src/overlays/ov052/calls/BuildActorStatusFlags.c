#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u16 flags;
} ActorBody;

typedef struct {
    u8 pad_000[0x230];
    ActorBody *body;
    u32 bodyFlags;
    u8 pad_238[0x75c - 0x238];
    int busy;
    u8 pad_760[0x9ac - 0x760];
    u64 stateFlags;
    u8 locked;
    u8 pad_9b5[0x9b8 - 0x9b5];
    int target;
    u8 pad_9bc[4];
    int mode;
    u8 pad_9c4[0xb68 - 0x9c4];
    u32 inputFlags;
} StatusActor;

extern BOOL IsBit0Set(u32 *flags);
extern BOOL func_ov021_020a9d24(u32 *flags);
extern BOOL func_ov001_020645c8(u32 value);

u32 BuildActorStatusFlags(StatusActor *actor)
{
    int mode = actor->mode;
    u32 result = 0;
    u64 flags;
    BOOL special;

    if (mode == 1 && !(actor->stateFlags & 8)) {
        if (mode != 1 || (actor->busy == 0 && !(actor->body->flags & 4))) {
            u64 wantHeld;
            if (actor->locked != 0 || !IsBit0Set(&actor->inputFlags) || func_ov001_020645c8(0x3520)) {
                goto set;
            }
            wantHeld = actor->stateFlags & 0x40;
            if (wantHeld) {
                if (!func_ov021_020a9d24(&actor->inputFlags)) {
                    goto skip;
                }
            } else if (!wantHeld && func_ov021_020a9d24(&actor->inputFlags)) {
                goto skip;
            }
        set:
            result |= 1;
        skip:;
        }
    }
    flags = actor->stateFlags;
    if ((flags & 0x800) && !(flags & 0x20000) && (actor->target == 0 || (actor->bodyFlags & 4))) {
        result |= 2;
    }
    special = TRUE;
    switch (mode) {
    case 0xb:
    case 0xc:
    case 0xd:
    case 0x15:
    case 0x16:
    case 0x18:
    case 0x1a:
        break;
    default:
        special = FALSE;
        break;
    }
    if (special) {
        result |= 4;
    }
    if (mode == 6 || mode == 0x10) {
        result |= 8;
    }
    if (flags & 0x20000) {
        result |= 0x10;
    }
    if (flags & 0x200000) {
        result |= 0x20;
    }
    if (mode == 0x18) {
        result |= 0x80;
    }
    if (flags & 0x20000000) {
        result |= 0x40;
    }
    return result;
}
