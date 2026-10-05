#include "nitro/types.h"

typedef struct QuantityPicker {
    u8 mode;
    u8 dirty;
    u8 pad2[2];
    u8 quantity;
    u8 maxQuantity;
    u8 swapped;
} QuantityPicker;

extern u16 data_02060500;
extern void PlaySoundEffect(int channel, int id);
extern void ArrangeWidgetPair(QuantityPicker *picker);

void StepPickerForward(QuantityPicker *picker)
{
    if (picker->mode == 2) {
        if ((data_02060500 & 0x10) == 0) {
            goto done;
        }
        picker->swapped ^= 1;
        ArrangeWidgetPair(picker);
    } else {
        if (picker->mode != 1 || picker->quantity >= picker->maxQuantity) {
            goto done;
        }
        if (picker->maxQuantity - picker->quantity >= 10) {
            picker->quantity += 10;
        } else {
            picker->quantity = picker->maxQuantity;
        }
    }
    PlaySoundEffect(0, 0);
done:
    picker->dirty = 1;
}
