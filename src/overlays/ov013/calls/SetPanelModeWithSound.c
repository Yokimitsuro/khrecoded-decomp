#include "nitro/types.h"

typedef struct {
    u8 pad_00[3];
    u8 mode;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void SetPanelModeWithSound(void) {
    data_ov013_02074ce0->mode = 1;
    PlaySoundEffect(2, 1);
}
