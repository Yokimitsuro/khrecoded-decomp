#include "nitro/types.h"

typedef struct SceneWork {
    u16 mode;
    u8 pad_02[0x1e];
    int gaugeEnabled;
    void *containerB;
    void *containerA;
    u8 pad_2c[0x0c];
    u8 elements[0x184c];
    u8 altObjects[0x138];
    u8 objects[0x48];
    void *container;
    u8 heapHolder[0x28];
} SceneWork;

extern SceneWork *data_ov045_020c08a0;

extern BOOL ReleaseRecordSlot(s32 slot);
extern void ReleaseRecordManager(void);
extern void func_ov027_020b833c(void *elements);
extern void func_ov027_020b7e1c(void *elements);
extern BOOL DestroyFndObjectList(void *container);
extern void ReleaseHeapBlockIfAllocated(void *holder);
extern void ZeroHalfThenFree(void *container);
extern void G3X_SetClearColor(unsigned color, unsigned alpha, unsigned depth, unsigned polygonId, BOOL fog);
extern void SetMenuGaugeActive(int index, BOOL enable);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG2CNT (*(vu16 *)0x0400000c)
#define REG_BG3CNT (*(vu16 *)0x0400000e)

void ShutdownScene(void)
{
    SceneWork *work = data_ov045_020c08a0;

    if (work->mode == 0) {
        ReleaseRecordSlot(0);
        ReleaseRecordManager();
        func_ov027_020b833c(work->elements);
        func_ov027_020b7e1c(work->elements);
        DestroyFndObjectList(work->objects);
        ReleaseHeapBlockIfAllocated(work->heapHolder);
        ZeroHalfThenFree(work->container);
    } else if (work->mode == 3) {
        ReleaseRecordSlot(0);
        ReleaseRecordManager();
        func_ov027_020b833c(work->elements);
        func_ov027_020b7e1c(work->elements);
        DestroyFndObjectList(work->altObjects);
    }
    ZeroHalfThenFree(work->containerA);
    ZeroHalfThenFree(work->containerB);
    REG_BG0CNT = (REG_BG0CNT & ~3) | 3;
    REG_BG1CNT = (REG_BG1CNT & ~3);
    REG_BG2CNT = (REG_BG2CNT & ~3) | 1;
    REG_BG3CNT = (REG_BG3CNT & ~3) | 2;
    G3X_SetClearColor(0, 0x1f, 0x7fff, 0x3f, FALSE);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0xf00;
    SetMenuGaugeActive(0, work->gaugeEnabled);
    data_ov045_020c08a0 = NULL;
}
