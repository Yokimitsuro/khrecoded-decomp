#include "nitro/types.h"

typedef struct Ov024Board {
    u8 pad_00[0x29];
    u8 slotBonus[6];
    u8 pad_2f[2];
    s8 slotValues[6];
    u8 pad_37[0x56 - 0x37];
    s8 slotItems[6];
    u8 itemMask;
    u8 rareMask;
    u8 rareChance;
    u8 pad_5f[3];
    s8 itemCount;
    u8 pad_63;
    u8 bonusCount;
    u8 penaltyCount;
    u8 pad_66[5];
    u8 itemPool;
    u8 pad_6c[8];
    int state;
    u8 pad_78[0x8c - 0x78];
    int fillAll;
} Ov024Board;

typedef struct GameSession {
    u8 pad_0000[0x28c8];
    u32 seed;
    u64 elapsed;
} GameSession;

extern GameSession *data_0205fe0c;
extern u32 func_0202a9e4(u32 range);
extern int func_ov024_020b6574(u32 mask);
extern s64 OS_GetTick(void);
extern s64 GetCardThreadStartTick(void);

void PlaceBoardBonuses(Ov024Board *board)
{
    int round;
    int start;
    int i;
    int slot;
    u32 seed;
    u64 elapsed;

    if (board->fillAll != 0 && board->itemPool != 0) {
        board->itemCount = 6;
    }
    for (round = 0; round < board->itemCount; round++) {
        start = func_0202a9e4(6);
        for (i = 0; i < 6; i++) {
            slot = (start + i) % 6;
            if (board->slotValues[slot] >= 0 && board->slotItems[slot] == 0) {
                board->slotItems[slot] = func_ov024_020b6574(board->itemPool) + 1;
                board->itemMask |= (u8)(1 << slot);
                break;
            }
        }
    }
    for (round = 0; round < board->bonusCount; round++) {
        start = func_0202a9e4(6);
        for (i = 0; i < 6; i++) {
            slot = (start + i) % 6;
            if (board->slotValues[slot] >= 0 && board->slotBonus[slot] == 0) {
                board->slotBonus[slot] = 1;
                break;
            }
        }
    }
    for (round = 0; round < board->penaltyCount; round++) {
        start = func_0202a9e4(6);
        for (i = 0; i < 6; i++) {
            slot = (start + i) % 6;
            if (board->slotValues[slot] >= 0 && board->slotBonus[slot] == 0) {
                board->slotBonus[slot] = 2;
                break;
            }
        }
    }
    elapsed = (u64)((OS_GetTick() - GetCardThreadStartTick()) << 6) / 0x1ff6210;
    seed = data_0205fe0c->seed + elapsed;
    if (board->rareChance > seed % 100) {
        start = seed % 6;
        for (i = 0; i < 6; i++) {
            slot = (start + i) % 6;
            if (board->slotValues[slot] >= 0 && !(board->rareMask & (1 << slot))) {
                board->rareMask |= (u8)(1 << slot);
                break;
            }
        }
    }
    board->state = 0;
}
