#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0x64f0];
    int active;
    u8 entity[0xa0];
} PanelState;

extern PanelState *data_ov025_020b7780;
extern void ResetFieldsToDefault(void *entity, int mode);

void ActivatePanelEntity(void) {
    data_ov025_020b7780->active = 1;
    ResetFieldsToDefault(data_ov025_020b7780->entity, 3);
}
