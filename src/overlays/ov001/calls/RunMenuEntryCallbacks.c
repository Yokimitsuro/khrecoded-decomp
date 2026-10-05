#include "nitro/types.h"

typedef struct ModeTable {
    int values[3];
} ModeTable;

typedef struct FieldState {
    u8 pad_0000[0x27b6];
    u8 lowFlags : 4;
    u8 hintShown : 1;
    u8 highFlags : 3;
} FieldState;

extern const ModeTable data_ov001_0209de90;
extern FieldState *data_ov001_020a0480;
extern BOOL func_ov001_020645c8(u32 flag);
extern void func_ov001_020716e8(int menu, int value);

void RunMenuEntryCallbacks(void *context, int menu, int count, void (*callback)(void *context, int index, int mode), int mode)
{
    ModeTable table = data_ov001_0209de90;
    int i;
    int value;
    BOOL skip;

    for (i = 0; i < count; i++) {
        callback(context, i, mode);
    }
    value = table.values[mode];
    if (value == 2) {
        if (menu == 0 && (func_ov001_020645c8(0x3525) || data_ov001_020a0480->hintShown)) {
            skip = TRUE;
        } else {
            skip = FALSE;
        }
        if (skip) {
            return;
        }
    }
    func_ov001_020716e8(menu, value);
}
