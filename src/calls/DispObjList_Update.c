#include "nitro/types.h"

typedef volatile u16 vu16;

#define REG_BLDALPHA    (*(vu16 *)0x04000052)
#define REG_DB_BLDALPHA (*(vu16 *)0x04001052)

struct ObjFlags { unsigned f0 : 1, f1 : 1, f2 : 1; };

extern void CP_SaveContext(void *lock);
extern void CPi_RestoreContext(void *lock);
extern void OamBuffer_Flush(void *manager, void *arg);
extern void DispObj_WriteOam(void *manager, void *obj);
extern void NNS_G2dTickCellAnimation(void *cellAnim, int frames);

void DispObjList_Update(int *manager, void *arg)
{
    u8 lock[28];
    void *obj;

    if (*manager == 0) {
        return;
    }

    CP_SaveContext(lock);

    if (manager[0x1807] != 0) {
        if (manager[0x1181] == 2) {
            REG_DB_BLDALPHA = manager[0x1809] | (0x10 - manager[0x1809]) << 8;
        } else {
            REG_BLDALPHA = manager[0x1809] | (0x10 - manager[0x1809]) << 8;
        }
    }

    for (obj = (void *)*manager; obj != 0; obj = *(void **)((int)obj + 4)) {
        if (((struct ObjFlags *)((char *)obj + 0x78))->f2) {
            DispObj_WriteOam(manager, obj);
        }
        if (((struct ObjFlags *)((char *)obj + 0x78))->f1) {
            NNS_G2dTickCellAnimation((void *)((int)obj + 0x14), 0x1000);
        }
    }

    manager[0x180c] = 0;
    OamBuffer_Flush(manager, arg);
    CPi_RestoreContext(lock);

    while ((*(vu16 *)0x04000280 & 0x8000) != 0) {
    }
}
