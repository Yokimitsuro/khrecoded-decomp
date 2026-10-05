#include "nitro/types.h"

typedef struct TaggedEntryTable TaggedEntryTable;

typedef struct MapLayout {
    u8 pad_0000[0x24e0];
    s16 chipIds[32];
    u8 pad_2520[0xd8c];
    u16 chipCountsA[5];
    u16 chipCountsB[4];
} MapLayout;

typedef struct GameState {
    u8 pad_0000[0x2c58];
    u32 activeChipMask;
    u8 pad_2C5C[0xe];
    u8 hasPartyAbilities;
    u8 pad_2C6B[0x14d];
    u16 partySlots[4];
} GameState;

typedef struct ChipRecord {
    u32 kind;
} ChipRecord;

typedef struct AbilitySlot {
    s32 abilityId;
    s32 unk_4;
} AbilitySlot;

typedef struct PartyRecord {
    u8 pad_00[0x20];
    AbilitySlot abilities[4];
} PartyRecord;

extern GameState *data_0205fe0c;
extern MapLayout *gMapLayout;

extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL func_02051e10(s32 slot);
extern PartyRecord *GetRecordSlotPair0Entry(s32 index);
extern ChipRecord *GetRecordSlotPair1Entry(s32 index);
extern void ReleaseHandle(TaggedEntryTable *table);
extern void *func_0204fe40(TaggedEntryTable *table, u32 id, int flag, u32 value);
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);

void BuildAbilityTable(TaggedEntryTable *table)
{
    u32 mask = data_0205fe0c->activeChipMask;
    MapLayout *map = gMapLayout;
    u32 countA = 0;
    u32 countB = 0;
    u32 countC = 0;
    u32 countD = 0;
    u32 countE = 0;
    u32 countF = 0;
    u32 countG = 0;
    u32 countH = 0;
    s16 *chipIds;
    int i;
    int slot;

    AcquireRecordManager();
    chipIds = map->chipIds;
    ReleaseHandle(table);
    for (i = 0; i < 5; i++) {
        u32 count = map->chipCountsA[i];
        if (count != 0) {
            if (count >= 100) {
                count = 100;
            }
            func_0204fe40(table, i, 1, count);
        }
    }
    for (i = 0; i < 4; i++) {
        u32 count = map->chipCountsB[i];
        if (count != 0) {
            if (count >= 100) {
                count = 100;
            }
            func_0204fe40(table, i + 5, 1, count);
        }
    }

    if (mask != 0) {
        AcquireRecordSlot(1, 1);
        for (i = 0; i < 32; i++, chipIds++) {
            if (*chipIds >= 0 && (mask & (1 << i))) {
                switch (GetRecordSlotPair1Entry(*chipIds)->kind) {
                case 0xf8:
                case 0xf9:
                case 0xfa:
                case 0xfb:
                    countA++;
                    break;
                case 0xfc:
                case 0xfd:
                    countB++;
                    break;
                case 0xfe:
                case 0xff:
                case 0x100:
                    countC++;
                    break;
                case 0x101:
                case 0x102:
                    countD++;
                    break;
                case 0x103:
                case 0x104:
                    countE++;
                    break;
                case 0x105:
                case 0x106:
                case 0x107:
                    countF++;
                    break;
                case 0x108:
                case 0x109:
                case 0x10a:
                    countG++;
                    break;
                case 0x10b:
                case 0x10c:
                    countH++;
                    break;
                default:
                    func_0204fe40(table, *chipIds, 1, 1);
                    break;
                }
            }
        }
        if (countA != 0) {
            func_0204fe40(table, 9, 1, countA);
        }
        if (countB != 0) {
            func_0204fe40(table, 10, 1, countB);
        }
        if (countC != 0) {
            func_0204fe40(table, 13, 1, countC);
        }
        if (countD != 0) {
            func_0204fe40(table, 14, 1, countD);
        }
        if (countE != 0) {
            func_0204fe40(table, 16, 1, countE);
        }
        if (countF != 0) {
            func_0204fe40(table, 18, 1, countF);
        }
        if (countG != 0) {
            func_0204fe40(table, 19, 1, countG);
        }
        if (countH != 0) {
            func_0204fe40(table, 20, 1, countH);
        }
        WriteGlobalPackedBits(0x1a0f, 3, countA);
        func_02051e10(1);
    }

    if (data_0205fe0c->partySlots[0] != 0xffff || data_0205fe0c->hasPartyAbilities) {
        slot = 0;
        AcquireRecordSlot(0, 1);
        do {
            if (data_0205fe0c->partySlots[slot] != 0xffff) {
                PartyRecord *record = GetRecordSlotPair0Entry(data_0205fe0c->partySlots[slot]);
                int k;
                for (k = 0; k < 4; k++) {
                    if (record->abilities[k].abilityId != -1) {
                        func_0204fe40(table, record->abilities[k].abilityId, 1, 1);
                    }
                }
            }
            slot++;
        } while (slot < 4);
        func_02051e10(0);
    }
    ReleaseRecordManager();
}
