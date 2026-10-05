#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern u32 func_ov001_0207b6b0(void);
extern void StoreToGlobalPtr4Field28(u32 a);

u32 TryEnterState7(void)
{
    u32 result;

    result = func_ov001_0207b6b0();
    if (result == 0) {
        return 0xffffffff;
    }
    if ((data_ov031_020bc820->flags & 1) != 0) {
        data_ov031_020bc820->flags = data_ov031_020bc820->flags & 0xfffe;
    }
    StoreToGlobalPtr4Field28(0);
    return 7;
}
