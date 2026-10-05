#include "nitro/types.h"

typedef struct {
    s32 mode;
    u32 flags;
} AiState;

typedef struct {
    u8 pad_0000[0x1258];
    AiState ai;
} Enemy;

void RefreshAiModeFromFlags(Enemy *enemy)
{
    AiState *ai = &enemy->ai;

    if (enemy->ai.mode == 6) {
        ai->mode = 1;
    }
    if (ai->flags & 0x80000) {
        ai->mode = 6;
    }
}
