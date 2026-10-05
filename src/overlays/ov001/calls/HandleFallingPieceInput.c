#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 isVisible;
    s32 isMirrored;
    fx32 height;
    void *sprite;
    u16 buttons;
} FallingPiece;

typedef struct {
    s32 mode;
    void *sprites[4];
    void *frameSprite;
    u8 pad_18[0x20 - 0x18];
    s32 isActive;
    FallingPiece pieces[6];
    s32 spawnTimer;
    s32 spawnIndex;
    fx32 fallSpeed;
    u16 lastIndex;
    u32 hitCount;
    u32 targetCount;
} FallingContext;

extern void func_ov001_0207e0e0(int phase);
extern void func_ov001_0207e118(int hitCount);

int HandleFallingPieceInput(FallingContext *context, u32 keys)
{
    int i;
    FallingPiece *piece;
    BOOL hit = FALSE;
    int result;

    if (!(keys & 0xc03)) {
        return 5;
    }
    for (i = 0; i < 6; i++) {
        piece = &context->pieces[i];
        if (piece->isVisible != 0 && piece->height >= 0x28000 && piece->height <= 0x46000) {
            BOOL match = FALSE;

            if ((keys & piece->buttons) && !(keys & ~piece->buttons)) {
                match = TRUE;
            }
            if (match) {
                piece->isVisible = 0;
                hit = TRUE;
            } else {
                piece->isVisible = 0;
            }
            break;
        }
    }
    if (hit) {
        context->hitCount++;
        func_ov001_0207e118(context->hitCount);
        if (context->hitCount == context->targetCount) {
            func_ov001_0207e0e0(0);
            result = 1;
            for (i = 0; i < 6; i++) {
                piece = &context->pieces[i];
                piece->isVisible = 0;
                context->spawnTimer = 0x7fffffff;
            }
        } else {
            func_ov001_0207e0e0(1);
            context->fallSpeed += 0x4cd;
            if (piece->isMirrored != 0) {
                result = 2;
            } else {
                result = 0;
            }
        }
    } else {
        func_ov001_0207e0e0(2);
        result = 4;
    }
    return result;
}
