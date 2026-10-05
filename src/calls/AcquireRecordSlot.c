#include "nitro/types.h"

extern int gRecordManager;

extern void LoadTextEntryTablesLarge(int param);
extern void LoadTextEntryTables(int param);
extern void LoadStringPointerTable(int param);
extern void func_0205162c(int param);
extern void func_02051724(int param);
extern void func_02051770(int param);
extern void LoadRelocatedOffsetTable(int param);
extern void func_0205182c(int param);
extern void func_02051878(int param);
extern void LoadRecordTables(int param);
extern void LoadLinkedEntryTables(int param);
extern void LoadNamedRecordTables(int param);
extern void func_02051ab8(int param);
extern void LoadStringPointerTableB(int param);

/* Bumps a record slot's reference count. */
int AcquireRecordSlot(int slot, int param)
{
    int manager;

    manager = gRecordManager;
    *(u8 *)(gRecordManager + 0x44 + slot) = *(u8 *)(gRecordManager + 0x44 + slot) + 1;
    if (*(u8 *)(manager + slot + 0x44) > 1) {
        return 1;
    }
    switch (slot) {
        case 0:
            LoadTextEntryTablesLarge(param);
            break;
        case 1:
            LoadTextEntryTables(param);
            break;
        case 2:
            LoadStringPointerTable(param);
            break;
        case 3:
            func_0205162c(param);
            break;
        case 4:
            func_02051724(param);
            break;
        case 5:
            func_02051770(param);
            break;
        case 6:
            LoadRelocatedOffsetTable(param);
            break;
        case 7:
            func_0205182c(param);
            break;
        case 8:
            func_02051878(param);
            break;
        case 9:
            LoadRecordTables(param);
            break;
        case 10:
            LoadLinkedEntryTables(param);
            break;
        case 11:
            LoadNamedRecordTables(param);
            break;
        case 12:
            func_02051ab8(param);
            break;
        case 13:
            LoadStringPointerTableB(param);
            break;
        }
    return 1;
}
