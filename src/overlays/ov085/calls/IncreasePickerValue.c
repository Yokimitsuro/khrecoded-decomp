#include "nitro/types.h"

typedef struct QuantityPicker {
    u8 mode;
    u8 dirty;
    u8 pad2[2];
    u8 quantity;
    u8 maxQuantity;
    u8 pad6[0x16];
    s16 entryCount;
} QuantityPicker;

extern void PlaySoundEffect(int channel, int id);

void IncreasePickerValue(QuantityPicker *picker)
{
    if (picker->mode == 0) {
        if (picker->entryCount > 1) {
            picker->dirty = 1;
            return;
        }
    } else if (picker->mode == 1 && picker->quantity < picker->maxQuantity) {
        picker->quantity++;
        picker->dirty = 1;
        PlaySoundEffect(0, 0);
    }
}
