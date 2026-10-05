#include "nitro/types.h"

typedef struct {
    u8 pad_000[4];
    u16 width;
    u16 row;
    u16 column;
} GridCursor;

typedef struct {
    u8 pad_0000[0x1a0];
    GridCursor cursor;
    u8 pad_01aa[0xcf1c - 0x1aa];
    int archive[3];
    u8 pad_cf28[0xd1b8 - 0xcf28];
    int clearedCount;
    u8 pad_d1bc[0xd1d0 - 0xd1bc];
    int step;
} SceneWork;

extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern void SetSceneState(int state, SceneWork *work);
extern void *func_ov027_020ba2c8(int *archive, int index);
extern void func_ov093_020c3c38(int x, int y, void *data, int cellIndex);
extern int func_ov093_020c3c44(void);

void RunUnlockSequence(SceneWork *work)
{
    GridCursor *cursor;
    int cellIndex;
    void *image;

    switch (work->step) {
    case 0:
        if (!IsGlobalPackedBitSet(0xf4c)) {
            if (work->clearedCount >= 20) {
                SetGlobalPackedBit(0xf4c);
                SetGlobalPackedBit(0xf4c + 0x204);
                work->step++;
            } else {
                SetSceneState(5, work);
            }
        } else {
            SetSceneState(5, work);
        }
        break;
    case 1:
        cursor = &work->cursor;
        cellIndex = cursor->column + cursor->width * cursor->row * 2;
        image = func_ov027_020ba2c8(work->archive, 7);
        func_ov093_020c3c38(0x80, 0x60, image, cellIndex);
        work->step++;
        break;
    case 2:
        if (func_ov093_020c3c44() == 0) {
            work->step = 0;
        }
        break;
    }
}
