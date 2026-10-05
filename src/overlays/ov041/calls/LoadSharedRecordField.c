#include "nitro/types.h"

extern u32 sOv041_MoPzZ_020cfac0;
extern int SND_RegisterSeq(void *table, int id);
extern void func_0202c6a4(int enable);
extern int AcquireOrRefreshResourceBlock(int record, int index, int type);
extern void IndexedPointer_GetFirstWord(int value, int key);
extern int NestedPointer_GetFirstWord(int value, int key, int flags);
extern void Tex0_GetTexPlttParams(void *dest, int value, int flags);
extern void ReleaseSharedRecordSlot(int record);

void LoadSharedRecordField(int owner) {
    int record;
    int value;

    record = SND_RegisterSeq(&sOv041_MoPzZ_020cfac0, 0x12);
    func_0202c6a4(0);
    value = AcquireOrRefreshResourceBlock(record, 0, 1);
    func_0202c6a4(1);
    IndexedPointer_GetFirstWord(value, 7);
    value = NestedPointer_GetFirstWord(value, 7, 0);
    Tex0_GetTexPlttParams((void *)(owner + 0x1dd0), value, 0);
    ReleaseSharedRecordSlot(record);
}
