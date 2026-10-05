#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern u32 AreAllListNodesReady(void);
extern u32 func_ov001_020871a0(void);

u32 TryEnterState3(void)
{
    u32 result;

    result = AreAllListNodesReady();
    if (result == 0) {
        return 0xffffffff;
    }
    func_ov001_020871a0();
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x8000;
    return 3;
}
