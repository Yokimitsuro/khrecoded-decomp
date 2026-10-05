#include "nitro/types.h"

typedef struct Ov037Context {
    s16 state;
    u16 entryCount;
    s32 freeSlots;
} Ov037Context;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 lowFlags : 11;
    u32 restrictedMenu : 1;
} FieldState;

extern Ov037Context *gContinueScreenContext;
extern FieldState *data_ov001_020a0480;
extern s32 data_0205fe20;
extern void func_ov037_020bb300(u32 slot, u32 entry);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);

void BuildMenuEntryList(void)
{
    gContinueScreenContext->entryCount = 0;
    if (data_ov001_020a0480->restrictedMenu) {
        func_ov037_020bb300(0, 0x19);
    } else {
        func_ov037_020bb300(0, 0);
        if (data_0205fe20 != 0) {
            func_ov037_020bb300(1, 1);
        }
        func_ov037_020bb300(2, 2);
        if (ReadSessionPackedBits(0x1a00, 2) == 3) {
            func_ov037_020bb300(3, 3);
        }
    }
    gContinueScreenContext->freeSlots = 0x12 - gContinueScreenContext->entryCount;
}
