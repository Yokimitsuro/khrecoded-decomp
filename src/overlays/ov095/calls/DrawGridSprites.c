#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 head[0x14];
    fx32 y;
    u8 tail[0x18];
} SpriteDesc;

typedef struct {
    u8 pad[0x34];
    int scroll;
} GridTable;

typedef struct {
    u8 pad0[0xcaec];
    SpriteDesc sprites[0xef];
    u8 pad1[0xff34 - 0xcaec - 0xef * 0x30];
    SpriteDesc badges[0x5d];
    u8 pad2[0x110a4 - 0xff34 - 0x5d * 0x30];
    GridTable table;
    u8 pad3[0x1114c - 0x110a4 - sizeof(GridTable)];
    int blinkPhase;
    BOOL badgeVisible[0xef];
} GridWork;

extern void func_ov001_0206aa7c(void);
extern void func_ov001_0206ad28(SpriteDesc *sprite);
extern BOOL IsEntryFlagSet_020c1340(int useSecondSet, int bitIndex);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#define INT_TO_FX32_ROUNDED(v) ((fx32)((float)(v) > 0.0f ? 0.5f + 4096.0f * (float)(v) : 4096.0f * (float)(v) - 0.5f))

void DrawGridSprites(GridWork *work) {
    GridTable *table = &work->table;
    SpriteDesc sprite;
    SpriteDesc badge;
    int i;

    func_ov001_0206aa7c();
    for (i = 0; i < 0xef; i++) {
        SpriteDesc *source = &work->sprites[i];
        int offset;

        if (IsEntryFlagSet_020c1340(0, i)) {
            MI_CpuCopy8(source, &sprite, sizeof(SpriteDesc));
            offset = -table->scroll;
            sprite.y += INT_TO_FX32_ROUNDED(offset);
            func_ov001_0206ad28(&sprite);
            if (i >= 0x58 && i <= 0xb4 && work->badgeVisible[i] != 0) {
                source = &work->badges[i - 0x58];
                if (IsEntryFlagSet_020c1340(0, i)) {
                    MI_CpuCopy8(source, &badge, sizeof(SpriteDesc));
                    offset = -table->scroll;
                    badge.y += INT_TO_FX32_ROUNDED(offset);
                    if (work->blinkPhase == 0) {
                        func_ov001_0206ad28(&badge);
                    }
                }
            }
        }
    }
}