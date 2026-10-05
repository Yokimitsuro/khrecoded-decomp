#include "nitro/types.h"

typedef struct {
    u8 pad_000[4];
    u16 width;
    u16 row;
    u16 column;
} GridCursor;

typedef struct {
    u8 pad_00[0x40];
    const char *name;
} RecordEntry;

typedef struct {
    u8 pad_0000[0x1a0];
    GridCursor cursor;
    u8 pad_01aa[0xcf1c - 0x1aa];
    int archive[3];
    u8 pad_cf28[0xd1d0 - 0xcf28];
    int step;
    u8 pad_d1d4[0xd1e0 - 0xd1d4];
    int prizeCount;
} SceneWork;

extern const char data_ov093_020c4e2c[];
extern const char data_ov093_020c4e48[];
extern const char data_ov093_020c4e64[];
extern const char data_ov093_020c4e80[];
extern void SetSceneState(int state, SceneWork *work);
extern RecordEntry *GetRecordSlotPair0Entry(s32 index);
extern void *func_ov027_020ba2c8(int *archive, int index);
extern int GetLanguageIndex(void);
extern void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...);
extern void func_ov093_020c3c38(int x, int y, void *data, int cellIndex);
extern int func_ov093_020c3c44(void);

void RunPrizeMessageSequence(SceneWork *work)
{
    char message[0x200];
    GridCursor *cursor;
    int cellIndex;
    const char *name;
    int *archive;
    void *prefix;
    void *suffix;

    switch (work->step) {
    case 0:
        if (work->prizeCount > 0) {
            work->step++;
            return;
        }
        SetSceneState(6, work);
        break;
    case 1:
        name = GetRecordSlotPair0Entry(0xca)->name;
        cursor = &work->cursor;
        cellIndex = cursor->column + cursor->width * cursor->row * 2;
        archive = work->archive;
        prefix = func_ov027_020ba2c8(archive, 8);
        suffix = func_ov027_020ba2c8(archive, 9);
        switch (GetLanguageIndex()) {
        case 3:
            OS_SNPrintf_0202e094(message, 0x100, data_ov093_020c4e2c, name, prefix, work->prizeCount, suffix);
            break;
        case 4:
            OS_SNPrintf_0202e094(message, 0x100, data_ov093_020c4e48, name, prefix, work->prizeCount, suffix);
            break;
        case 1:
            OS_SNPrintf_0202e094(message, 0x100, data_ov093_020c4e64, suffix, name, prefix, work->prizeCount);
            break;
        case 0:
        case 2:
        case 5:
        default:
            OS_SNPrintf_0202e094(message, 0x100, data_ov093_020c4e80, name, prefix, work->prizeCount, suffix);
            break;
        }
        func_ov093_020c3c38(0x80, 0x60, message, cellIndex);
        work->step++;
        break;
    case 2:
        if (func_ov093_020c3c44() == 0) {
            work->prizeCount = 0;
            work->step = 0;
        }
        break;
    }
}
