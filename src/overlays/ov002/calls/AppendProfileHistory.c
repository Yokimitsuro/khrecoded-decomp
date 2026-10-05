#include "nitro/types.h"

typedef struct ProfileSource {
    u8 key[0x10];
    u16 name[0xb];
    u16 message[0x1b];
    u16 iconId;
    u8 pad_5E[7];
    u8 attrA;
    u8 attrB;
    u8 attrC;
    u8 attrD;
    u8 pad_69[2];
    u8 attrE;
    u8 attrF;
} ProfileSource;

typedef struct ProfileRecord {
    u8 name[0xf];
    u8 message[0x27];
    u16 iconId;
    u32 attrA : 4;
    u32 attrB : 5;
    u32 attrC : 5;
    u32 attrD : 3;
    u32 flag17 : 1;
    u32 flag18 : 1;
    u32 unused19 : 1;
    u32 attrE : 4;
    u32 attrF : 1;
    u32 unused25 : 7;
    u8 key[0x10];
} ProfileRecord;

typedef struct ProfileHistory {
    ProfileRecord records[0x5a];
    u8 pad_1AB8[0x10];
    u32 count : 7;
    u32 rest : 25;
} ProfileHistory;

extern ProfileHistory *func_ov002_02066fe0(void);
extern void MI_CpuFill8(void *dest, int value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void PackWideChars12(const u16 *src, int length, u8 *dest, int destSize);
extern void RemoveContextSlot(int index);
extern void func_02027390(int id, int kind, int delta, int limit);

void AppendProfileHistory(ProfileSource *source)
{
    ProfileHistory *history = func_ov002_02066fe0();
    ProfileRecord record;

    MI_CpuFill8(&record, 0, sizeof(record));
    PackWideChars12(source->name, 10, record.name, 0xf);
    PackWideChars12(source->message, 0x1a, record.message, 0x27);
    record.iconId = source->iconId;
    MI_CpuCopy8(source->key, record.key, 0x10);
    record.attrC = source->attrC;
    record.attrA = source->attrA;
    record.attrD = source->attrD;
    record.flag17 = 0;
    record.attrB = source->attrB;
    record.flag18 = 0;
    record.attrE = source->attrE;
    if (source->attrF) {
        record.attrF = 1;
    } else {
        record.attrF = 0;
    }
    if (history->count >= 0x5a) {
        RemoveContextSlot(0);
    }
    MI_CpuCopy8(&record, &history->records[history->count], sizeof(record));
    history->count = history->count + 1;
    func_02027390(0xb48, 0x11, 1, 99999);
}
