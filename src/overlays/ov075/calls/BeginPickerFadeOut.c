#include "nitro/types.h"

typedef struct FadeAnim {
    u8 data[0x24];
} FadeAnim;

typedef struct ItemPicker {
    int mode;
    u8 pad_0004[0x9c14 - 0x4];
    FadeAnim fade;
    u32 visible : 1;
    u32 unk_1 : 1;
    u32 active : 1;
    u32 unk_3 : 29;
} ItemPicker;

extern void func_02052528(FadeAnim *anim, int start, int end, int delay, int duration);
extern void func_02052570(FadeAnim *anim);

void BeginPickerFadeOut(ItemPicker *picker)
{
    if (picker->mode != 3) {
        picker->mode = 3;
        picker->visible = FALSE;
        picker->active = FALSE;
        func_02052528(&picker->fade, 0, 0x1000, 0, 0x50);
        func_02052570(&picker->fade);
    }
}