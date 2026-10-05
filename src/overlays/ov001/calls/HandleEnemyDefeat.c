#include "nitro/types.h"

typedef struct EnemyRecord {
    u8 kind;
    u8 variant;
    u8 pad_02[6];
    s16 counterAmount;
    u8 pad_0a[2];
} EnemyRecord;

typedef struct EnemyTable {
    u32 unk0;
    EnemyRecord *records;
} EnemyTable;

typedef struct EnemyTableHolder {
    EnemyTable *table;
} EnemyTableHolder;

extern EnemyTableHolder *data_ov001_020a0490;
extern void func_ov001_0206671c(s32 amount, u32 position, u32 kind);
extern int func_ov001_020644b0(void);
extern u32 func_ov032_020bb88c(u8 kind);
extern int func_ov001_02063a38(void);
extern BOOL func_ov035_020bae94(void);
extern BOOL func_ov001_020645c8(u32 flagId);
extern void func_ov001_02063a80(int index, int amount);
extern u8 func_ov001_02068530(u32 id);
extern void RollEnemyDrop(int level, int recordId, u32 owner, BOOL reduced);
extern void func_02027390(int messageId, int category, int amount, int limit);
extern void AddRegionProgress(u8 enabled);
extern void SetGlobalPackedBit(u32 bit);

void HandleEnemyDefeat(s32 group, s32 index, u32 position, BOOL notify, int level)
{
    EnemyTableHolder *holder = data_ov001_020a0490;
    BOOL dropItem = TRUE;
    BOOL countKill = TRUE;
    EnemyRecord *record;
    int kind;
    int dropId;

    if (group < 0 && index < 0) {
        func_ov001_0206671c(1000, position, 4);
        return;
    }
    record = &holder->table->records[index];
    kind = record->kind;
    if (func_ov001_020644b0() == 900) {
        kind = func_ov032_020bb88c(record->kind);
    }
    if (func_ov001_02063a38() == 6) {
        dropItem = FALSE;
        if (!func_ov035_020bae94()) {
            countKill = FALSE;
        }
    }
    if (func_ov001_020644b0() == 500) {
        if ((kind == 0xb && record->variant != 0) || (kind == 0xc && record->variant != 0)) {
            dropItem = FALSE;
        }
    }
    if (func_ov001_020645c8(0x3631)) {
        dropItem = FALSE;
    }
    if (func_ov001_02063a38() == 4) {
        func_ov001_02063a80(0, record->counterAmount);
    }
    switch (kind) {
    case 0x25:
    case 0x35:
    case 0x38:
    case 0x3b:
        func_ov001_02063a80(0, record->counterAmount);
        break;
    }
    dropId = func_ov001_02068530(kind);
    if (dropId == 0x28) {
        dropItem = FALSE;
        countKill = FALSE;
    }
    if (dropItem) {
        RollEnemyDrop(level, dropId, position, FALSE);
    }
    if (countKill) {
        func_02027390(dropId * 0x11 + 0x680, 0x11, 1, 99999);
        AddRegionProgress(notify != 0);
    }
    switch (kind) {
    case 0x1a:
        SetGlobalPackedBit(0xbe5);
        return;
    case 0x3e:
        SetGlobalPackedBit(0xbe7);
        return;
    case 0x41:
        SetGlobalPackedBit(0xbe6);
        return;
    }
}
