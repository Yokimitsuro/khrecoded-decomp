#include "nitro/types.h"

typedef struct OwnerInfo {
    u8 language;
    u8 favoriteColor;
    u8 birthMonth;
    u8 birthDay;
    u16 nickName[11];
    u16 nickNameLength;
    u16 comment[27];
    u16 commentLength;
} OwnerInfo;

typedef struct RecordB {
    u8 pad_00[8];
    s32 tag;
} RecordB;

typedef struct RecordC {
    u8 pad_00[6];
    s16 recordIndices[20];
} RecordC;

extern u32 data_020534b8[];

/* Unsigned divide helper returns the remainder in r1. */
extern u64 _u32_div_f(u32 dividend, u32 divisor);

extern void OS_GetMacAddress(void *dest);
extern void OS_GetOwnerInfo(OwnerInfo *info);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL func_02051e10(s32 slot);
extern RecordC *GetRecordTableCEntry(s32 index);
extern RecordB *GetRecordTableBEntry(s32 index);
extern s32 SetSharedFlagBits(u32 handle);
extern BOOL EquipRecordList(s32 *recordIndices, s32 count);
extern u32 func_0202a9e4(u32 range);
extern s32 PickRandomRecordInCategory(s32 category, s32 requiredTag);

void GrantStartingRecords(void)
{
    s32 recordIndex;
    u8 macAddress[6];
    OwnerInfo owner;
    s32 tag = -1;
    u32 seed = 0;
    u16 setIndex;
    s16 *setRecords;
    s32 i;

    OS_GetMacAddress(macAddress);
    OS_GetOwnerInfo(&owner);
    for (i = 0; i < 6; i++) {
        seed += macAddress[i];
    }
    for (i = 0; i < owner.nickNameLength; i++) {
        seed += owner.nickName[i];
    }
    setIndex = (u32)(_u32_div_f(seed, 91) >> 32);
    if (setIndex >= 8) {
        setIndex++;
    }
    if (setIndex >= 0x35) {
        setIndex++;
    }
    AcquireRecordSlot(9, 1);
    AcquireRecordSlot(10, 1);
    setRecords = GetRecordTableCEntry(setIndex)->recordIndices;
    for (i = 0; i < 20; i++) {
        if (i == 18) {
            continue;
        }
        recordIndex = setRecords[i];
        if (recordIndex == -1) {
            continue;
        }
        SetSharedFlagBits(recordIndex);
        if (tag == -1 && i >= 6) {
            RecordB *record = GetRecordTableBEntry(recordIndex);
            if (record->tag != -1) {
                tag = record->tag;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        recordIndex = i;
        SetSharedFlagBits(recordIndex);
        if (i == 0) {
            EquipRecordList(&recordIndex, 1);
        }
    }
    for (i = 0; i < 5; i++) {
        recordIndex = i + 0x10;
        SetSharedFlagBits(recordIndex);
        if (i == 0) {
            EquipRecordList(&recordIndex, 1);
        }
    }
    for (i = 0; i < 0x21; i++) {
        recordIndex = i + 0x20;
        SetSharedFlagBits(recordIndex);
        if (i == 0) {
            EquipRecordList(&recordIndex, 1);
        }
    }
    for (i = 0; i < 11; i++) {
        recordIndex = data_020534b8[i];
        SetSharedFlagBits(recordIndex);
        if (i == 0) {
            EquipRecordList(&recordIndex, 1);
        }
    }
    for (i = 3; i < 20; i++) {
        recordIndex = PickRandomRecordInCategory(i + 1, func_0202a9e4(100) < 70 ? tag : -1);
        if (recordIndex != -1) {
            SetSharedFlagBits(recordIndex);
        }
    }
    for (i = 0; i < 20; i++) {
        if (i == 18) {
            continue;
        }
        recordIndex = setRecords[i];
        if (recordIndex == -1) {
            continue;
        }
        EquipRecordList(&recordIndex, 1);
    }
    func_02051e10(10);
    func_02051e10(9);
}
