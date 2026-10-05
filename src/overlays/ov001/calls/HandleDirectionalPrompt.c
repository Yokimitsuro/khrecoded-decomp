#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    u16 angle;
    u8 pad_26[0x2];
    s16 offsetY;
    u16 heldMask;
    u8 pad_2C[0x80];
    s32 hitCount;
    s32 hitTotal;
} DirectionalPrompt;

extern void func_ov001_0207e118(int hitCount);
extern void LoadMenuPhaseGraphics(int phase);

int HandleDirectionalPrompt(DirectionalPrompt *prompt, u32 keys) {
    BOOL hit = FALSE;
    int angle;

    if (prompt->hitCount >= prompt->hitTotal) {
        return 5;
    }
    angle = prompt->angle;
    if ((u32)angle <= 0x1000 || (u32)angle >= 0xf000) {
        prompt->heldMask &= 1;
        if (keys & 0xc03) {
            if ((keys & 1) && !(keys & ~1) && !(prompt->heldMask & 1)) {
                hit = TRUE;
            }
            prompt->heldMask |= 1;
        }
    } else if (angle >= 0x3000 && angle <= 0x5000) {
        prompt->heldMask &= 2;
        if (keys & 0xc03) {
            if ((keys & 2) && !(keys & ~2) && !(prompt->heldMask & 2)) {
                hit = TRUE;
            }
            prompt->heldMask |= 2;
        }
    } else if (angle >= 0xb000 && angle <= 0xd000) {
        prompt->heldMask &= 4;
        if (keys & 0xc03) {
            if ((keys & 0x400) && !(keys & ~0x400) && !(prompt->heldMask & 4)) {
                hit = TRUE;
            }
            prompt->heldMask |= 4;
        }
    } else if (angle >= 0x7000 && angle <= 0x9000) {
        prompt->heldMask &= 8;
        if (keys & 0xc03) {
            if ((keys & 0x800) && !(keys & ~0x800) && !(prompt->heldMask & 8)) {
                hit = TRUE;
            }
            prompt->heldMask |= 8;
        }
    }
    if (!(keys & 0xc03)) {
        return 3;
    }
    if (hit) {
        func_ov001_0207e118(++prompt->hitCount);
        if (prompt->hitCount == prompt->hitTotal) {
            LoadMenuPhaseGraphics(0);
            return 1;
        }
        LoadMenuPhaseGraphics(1);
        prompt->offsetY += 0x60;
        return 0;
    }
    LoadMenuPhaseGraphics(2);
    return 4;
}
