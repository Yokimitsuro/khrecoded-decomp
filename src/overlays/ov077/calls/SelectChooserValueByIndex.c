#include "nitro/types.h"

typedef struct {
    u8 pad[0x1c];
    u32 selected;
    u32 *values;
} Chooser;

void SelectChooserValueByIndex(u32 index, Chooser *chooser)
{
    u32 *values = chooser->values;
    if (index <= 2) {
        index--; chooser->selected = (u8)values[index];
    }
}
