#include "nitro/types.h"

typedef struct SelectionStats {
    u8 level;
    u8 pad_01;
    u16 hp;
    u16 maxHp;
    u16 attack;
    u16 defense;
    u16 magic;
    u16 extra;
} SelectionStats;

typedef struct StatScaleTable {
    int scale[2][4][4];
} StatScaleTable;

typedef struct SaveOptions {
    u32 difficulty : 2;
    u32 rest : 30;
} SaveOptions;

extern u8 *data_0205fe0c;
extern const StatScaleTable data_02055a78;

extern SelectionStats *GetOverlaySelectionRecord(int index);
extern BOOL ArmObject(void);

void ApplySelectionStatScaling(int index, int level)
{
    SelectionStats *record = GetOverlaySelectionRecord(index);
    SelectionStats *base = GetOverlaySelectionRecord(0);
    int hp = record->hp;
    int difficulty = ((SaveOptions *)(data_0205fe0c + 0x2878))->difficulty;
    StatScaleTable table = data_02055a78;

    *record = *base;
    record->level = level;
    record->maxHp = (record->maxHp * table.scale[level - 1][difficulty][0] + 0xfff) >> 12;
    if (!ArmObject()) {
        record->maxHp = 1;
    }
    record->hp = hp > record->maxHp ? record->maxHp : (hp < 0 ? 0 : hp);
    record->attack = (record->attack * table.scale[level - 1][difficulty][1] + 0xfff) >> 12;
    record->defense = (record->defense * table.scale[level - 1][difficulty][2] + 0xfff) >> 12;
    record->magic = (record->magic * table.scale[level - 1][difficulty][3] + 0xfff) >> 12;
}
