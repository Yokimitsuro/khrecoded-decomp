#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    u8 refCounts[14];
} RecordManager;

extern RecordManager *gRecordManager;

extern void FreeRecordSlotPair0(void);
extern void FreeRecordSlotPair1(void);
extern void FreeRecordSlotPair2(void);
extern void FreeRecordSlotPair3(void);
extern void FreeRecordSlot4(void);
extern void FreeRecordSlot5(void);
extern void FreeRecordSlot6(void);
extern void FreeRecordSlot7(void);
extern void FreeRecordSlot8(void);
extern void ReleaseRecordTableA(void);
extern void ReleaseRecordTableB(void);
extern void ReleaseRecordTableC(void);
extern void ReleaseRecordTableD(void);
extern void ReleaseRecordTableE(void);

/* Drops a record slot's reference count. */
BOOL ReleaseRecordSlot(s32 slot)
{
    RecordManager *manager = gRecordManager;

    if (manager->refCounts[slot] == 0) {
        return FALSE;
    }
    manager->refCounts[slot]--;
    if (manager->refCounts[slot] != 0) {
        return TRUE;
    }
    switch (slot) {
    case 0:
        FreeRecordSlotPair0();
        break;
    case 1:
        FreeRecordSlotPair1();
        break;
    case 2:
        FreeRecordSlotPair2();
        break;
    case 3:
        FreeRecordSlot4();
        break;
    case 4:
        FreeRecordSlot5();
        break;
    case 5:
        FreeRecordSlot6();
        break;
    case 6:
        FreeRecordSlot7();
        break;
    case 7:
        FreeRecordSlot8();
        break;
    case 8:
        ReleaseRecordTableA();
        break;
    case 9:
        ReleaseRecordTableB();
        break;
    case 10:
        ReleaseRecordTableC();
        break;
    case 11:
        ReleaseRecordTableD();
        break;
    case 12:
        ReleaseRecordTableE();
        break;
    case 13:
        FreeRecordSlotPair3();
        break;
    }
    return TRUE;
}
