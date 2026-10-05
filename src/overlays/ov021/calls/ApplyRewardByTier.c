#include "nitro/types.h"

typedef struct PartyStats {
    u8 pad_00[2];
    u16 currentHp;
} PartyStats;

typedef struct PartyMember {
    u8 pad_000[0x1d4];
    PartyStats *stats;
} PartyMember;

typedef struct GameSession {
    u8 pad_0000[0x28d0];
    u32 money;
} GameSession;

extern GameSession *data_0205fe0c;
extern int func_ov001_0206dc38(void);
extern PartyMember *GetBoundedEntryField(int index);
extern void AddClampedHealth(PartyMember *member, s16 amount);
extern void func_ov001_02063a80(int counterId, int amount);
extern void func_ov001_02063d4c(int id, int amount);
extern int func_ov001_02064784(void);
extern int ReadSessionPackedBits(int bitOffset, int bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void func_0204f854(void);

void ApplyRewardByTier(int unused, int kind, int tier)
{
    int amount = 0;
    int index;
    s16 level;
    s8 maxLevel;

    switch (kind) {
    case 0:
        switch (tier) {
        case 0:
            amount = 1;
            break;
        case 1:
            amount = 10;
            break;
        case 2:
            amount = 100;
            break;
        }
        if (amount > 0) {
            for (index = 0; index < func_ov001_0206dc38(); index++) {
                PartyMember *member = GetBoundedEntryField(index);
                if (member->stats->currentHp != 0) {
                    AddClampedHealth(member, amount);
                }
            }
        }
        break;
    case 2:
        switch (tier) {
        case 0:
            amount = 10;
            break;
        case 1:
            amount = 100;
            break;
        case 2:
            amount = 1000;
            break;
        }
        if (amount > 0) {
            func_ov001_02063a80(0, amount);
        }
        break;
    case 3:
        switch (tier) {
        case 0:
            amount = 1;
            break;
        case 1:
            amount = 10;
            break;
        case 2:
            amount = 100;
            break;
        }
        if (amount > 0) {
            func_ov001_02063d4c(5, amount * 1000);
        }
        break;
    case 1:
        switch (tier) {
        case 0:
            amount = 1;
            break;
        case 1:
            amount = 10;
            break;
        case 2:
            amount = 100;
            break;
        }
        if (amount > 0) {
            data_0205fe0c->money = data_0205fe0c->money + amount > 999999 ? 999999 : data_0205fe0c->money + amount;
        }
        break;
    case 4:
        switch (tier) {
        case 0:
            amount = 1;
            break;
        case 1:
            amount = 10;
            break;
        case 2:
            amount = 100;
            break;
        }
        if (amount > 0) {
            func_ov001_02063a80(1, amount);
            func_ov001_02063a80(2, amount);
        }
        break;
    case 5:
        if (func_ov001_02064784() == 6) {
            level = ReadSessionPackedBits(0x3700, 0x10);
            maxLevel = ReadSessionPackedBits(0x3710, 3) + 1;
            switch (tier) {
            case 0:
                amount = 1;
                break;
            case 1:
                amount = 2;
                break;
            case 2:
                amount = 3;
                break;
            }
            level += (s16)amount;
            if (level >= maxLevel * 20) {
                level = maxLevel * 20;
            }
            WriteSessionPackedBits(0x3700, 0x10, level);
            func_0204f854();
        }
        break;
    case 6:
        break;
    }
}
