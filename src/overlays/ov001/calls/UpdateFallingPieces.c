#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 isVisible;
    s32 isMirrored;
    fx32 height;
    void *sprite;
    u16 size;
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
} FallingContext;

extern FallingContext *data_ov001_020a04f4;
extern void SpawnFallingPiece(FallingContext *context, FallingPiece *piece);
extern void UpdateFallingPiecePosition(FallingPiece *piece);
extern void func_ov001_0207e2d0(void);

extern void func_ov001_0206ad1c(void *arg);

s32 UpdateFallingPieces(void)
{
    FallingContext *context = data_ov001_020a04f4;
    FallingPiece *piece;
    s32 i;

    if (context->isActive != 0) {
        context->spawnTimer--;
        if (context->spawnTimer < 0) {
            context->spawnTimer = 15;
            SpawnFallingPiece(context, &context->pieces[context->spawnIndex]);
            context->spawnIndex = (context->spawnIndex + 1) % 6;
        }
        func_ov001_0207e2d0();
        for (i = 0; i < 6; i++) {
            piece = &context->pieces[i];
            if (piece->isVisible != 0) {
                piece->height -= context->fallSpeed;
                UpdateFallingPiecePosition(piece);
                func_ov001_0206ad1c(piece->sprite);
            }
        }
        func_ov001_0206ad1c(context->frameSprite);
    }
    return 0;
}
