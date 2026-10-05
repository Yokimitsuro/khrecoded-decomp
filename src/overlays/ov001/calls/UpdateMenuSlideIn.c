#include "nitro/types.h"

typedef struct Tween Tween;
typedef struct TileTable TileTable;

typedef struct FieldMenu {
    u8 pad_000[0x47c];
    int state;
    u8 pad_480[0x15c];
    u8 tween[0x18];
    u32 unk5f4_0 : 2;
    u32 finished : 1;
    u32 unk5f4_3 : 29;
    u8 pad_5f8[0xc];
    int offset;
} FieldMenu;

extern TileTable *func_ov001_0207123c(void);
extern void SampleTweenValue(Tween *tween, s32 *out);
extern void func_ov001_0207a880(int value);
extern void SetMenuHiddenAndReloadChars(int hidden);
extern void func_ov027_020b9d38(TileTable *table, int id);

void UpdateMenuSlideIn(FieldMenu *menu)
{
    TileTable *widgets = func_ov001_0207123c();
    s32 value;

    SampleTweenValue((Tween *)menu->tween, &value);
    if (menu->finished) {
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x100;
        menu->offset = -2;
        menu->state = 2;
        func_ov001_0207a880(0);
        SetMenuHiddenAndReloadChars(1);
        func_ov027_020b9d38(widgets, 9);
        func_ov027_020b9d38(widgets, 10);
        func_ov027_020b9d38(widgets, 11);
        *(vu32 *)0x04000014 = 0;
        return;
    }
    menu->offset = value >> 12;
}
