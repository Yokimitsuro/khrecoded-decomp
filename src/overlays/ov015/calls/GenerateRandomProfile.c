#include "nitro/types.h"

typedef struct {
    int values[6];
} RangeTable;

typedef struct {
    u8 pad_00[0x38];
    const u16 *name;
    const u16 *title;
} RecordD;

typedef struct {
    u8 pad_00[0x10];
    u16 name[11];
    u16 title[28];
    u8 slots[6];
    u8 rare;
    u8 classId;
    u8 level;
    u8 rank;
    u8 style;
    u8 pad_69[2];
    u8 emblem;
    u8 valid;
} PlayerProfile;

extern const RangeTable data_ov015_0207a1c8;

extern unsigned int func_0202a9e4(u16 range);
extern RecordD *GetRecordTableDEntry(s32 index);
extern u16 *CopyWideStringBounded(u16 *dst, const u16 *src, int maxLength);
extern void FillCategoryRecords(void *dest, void *preset);

void GenerateRandomProfile(PlayerProfile *profile, BOOL fillSlots) {
    RangeTable ranges = data_ov015_0207a1c8;
    int recordId = func_0202a9e4(0x32) + 0x32;
    RecordD *record = GetRecordTableDEntry(recordId);
    int i;

    CopyWideStringBounded(profile->name, record->name, 10);
    CopyWideStringBounded(profile->title, record->title, 0x1a);
    if (func_0202a9e4(1000) < 10) {
        profile->rare = 1;
    }
    profile->classId = func_0202a9e4(6);
    profile->level = func_0202a9e4(0x1e);
    profile->rank = func_0202a9e4(ranges.values[profile->classId]);
    profile->style = func_0202a9e4(6);
    profile->emblem = func_0202a9e4(9);
    FillCategoryRecords(profile, NULL);
    profile->valid = 1;
    if (fillSlots) {
        profile->slots[0] = recordId;
        for (i = 1; i < 6; i++) {
            profile->slots[i] = 0xff;
        }
    }
}
