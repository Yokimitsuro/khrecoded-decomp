#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcac0];
    u16 entryName[0x48];
    u8 *groupEntries[0x14];
    u8 pad_cba0[0xcf74 - 0xcba0];
    s16 group;
    u8 pad_cf76[2];
    s16 index;
    u16 groupWidth;
    s16 selection;
    s16 count;
} PanelState;

extern PanelState *data_ov014_0206f9a0;
extern u8 data_ov014_0206f81c[][7];
extern char data_ov014_0206f954[];

extern void func_ov002_0206203c(int selector);
extern void func_ov002_020620fc(int selector);
extern int DispatchContextCommand(int command, int value, int extra, void *buffer);
extern int GetPackedField(void *info, int category, int entry);
extern void *func_ov002_020621c4(int index, int extra);
extern void func_ov002_02061e34(int a, int b, int x, int y, int c, int d, int e, int f, const void *text);
extern void *SPrintfUnbounded(void *dst, const char *fmt, ...);
extern void CopyRecordName(s32 category, s32 index, u16 *dst);

void DrawSelectedEntryInfo(BOOL keepLayer)
{
    u16 text[0x20] = {0};
    u8 category;
    u8 entry;

    if (!keepLayer) {
        func_ov002_0206203c(-1);
    }
    func_ov002_020620fc(1);
    category = data_ov014_0206f81c[data_ov014_0206f9a0->group][data_ov014_0206f9a0->index];
    entry = data_ov014_0206f9a0->groupEntries[category][data_ov014_0206f9a0->selection];
    if (DispatchContextCommand(0xe, 0, 0, 0) == 1) {
        if (entry == GetPackedField(0, category, entry)) {
            func_ov002_02061e34(1, 1, 0x30, 0x26, 2, 8, 0, 1, func_ov002_020621c4(0x71, 0));
        }
        if (data_ov014_0206f9a0->count != 0) {
            SPrintfUnbounded(text, data_ov014_0206f954, data_ov014_0206f9a0->selection + 1,
                          data_ov014_0206f9a0->count);
            func_ov002_02061e34(1, 1, 0x40, 0x6a, 2, 0xc, 1, 0, text);
        }
    }
    CopyRecordName(category, entry, data_ov014_0206f9a0->entryName);
    func_ov002_02061e34(1, 1, 0x80, 0xb3, 2, 0xc, 1, 0, data_ov014_0206f9a0->entryName);
}
