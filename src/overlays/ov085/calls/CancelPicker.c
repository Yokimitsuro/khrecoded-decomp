#include "nitro/types.h"

typedef struct QuantityPicker {
    u8 mode;
    u8 dirty;
    u8 pad2[4];
    u8 swapped;
    u8 pad7;
    int selected;
} QuantityPicker;

extern void PopStackEntry(void);
extern void StartSubScene(int a, int b, int c);
extern void PlaySoundEffect(int channel, int id);
extern void func_ov085_020c0bb0(QuantityPicker *picker, u8 confirm);

void CancelPicker(QuantityPicker *picker)
{
    switch (picker->mode) {
    case 0:
        PopStackEntry();
        StartSubScene(7, -1, 1);
        PlaySoundEffect(0, 3);
        break;
    case 1:
        PlaySoundEffect(0, 3);
        func_ov085_020c0bb0(picker, 0);
        break;
    case 2: {
        BOOL confirm = FALSE;

        PlaySoundEffect(0, 3);
        picker->swapped = 1;
        if (picker->selected == 0) {
            confirm = TRUE;
        }
        func_ov085_020c0bb0(picker, confirm);
        break;
    }
    }
}
