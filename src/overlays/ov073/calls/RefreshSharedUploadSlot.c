#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[2];
    u8 flags;
    u8 pad_04[0xc8c - 4];
    u8 uploads[0x1c];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);
extern void func_ov027_020b9e20(void *uploads, int slotId);
extern void func_ov027_020b9e80(void *uploads);

void RefreshSharedUploadSlot(void)
{
    MenuSharedState *state = func_ov039_020bc650();

    func_ov027_020b9e20(state->uploads, 0x1a);
    if ((state->flags & 2) == 0) {
        func_ov027_020b9e80(state->uploads);
    }
}
