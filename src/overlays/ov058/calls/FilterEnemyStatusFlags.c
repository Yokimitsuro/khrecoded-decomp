#include "nitro/types.h"

typedef struct PlayerInfo PlayerInfo;
struct PlayerInfo {
    u8 pad_000[0x21c];
    u32 (*flagsCallback)(PlayerInfo *info);
};

typedef struct {
    u8 pad_000[0x9ac];
    u64 stateFlags;
    u8 pad_9b4[0x9c0 - 0x9b4];
    s32 mode;
} Enemy;

extern u32 BuildActorStatusFlags(Enemy *enemy);
extern PlayerInfo *GetBoundedEntryField(int index);

u32 FilterEnemyStatusFlags(Enemy *enemy)
{
    u32 flags = BuildActorStatusFlags(enemy);
    u32 playerFlags;
    PlayerInfo *player;
    s32 mode = enemy->mode;

    if (!(flags & 1)) {
        BOOL allowed = TRUE;

        if (mode != 0xf && mode != 0x1e) {
            allowed = FALSE;
        }
        if (!allowed) {
            goto checkGuard;
        }
        flags |= 1;
    }
    if (enemy->stateFlags & 0x800000) {
        flags &= ~1;
    }
    if (flags & 1) {
        playerFlags = 0;
        player = GetBoundedEntryField(0);
        if (player->flagsCallback != NULL) {
            playerFlags = player->flagsCallback(player);
        }
        if (!(playerFlags & 1)) {
            flags &= ~1;
        }
    }
checkGuard:
    if ((flags & 2) && (enemy->stateFlags & 0x800000)) {
        flags &= ~2;
    }
    return flags;
}
