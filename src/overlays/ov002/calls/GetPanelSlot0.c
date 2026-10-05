#include "nitro/types.h"

extern u8 *data_ov002_0206c460;

void *GetPanelSlot0(void) {
    void *slot = NULL;
    if (data_ov002_0206c460 != NULL) {
        slot = data_ov002_0206c460 + 0x30;
    }
    return slot;
}
