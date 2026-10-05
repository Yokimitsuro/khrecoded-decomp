#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    u32 unk_48;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern u32 func_ov001_02068084(void);
extern void WriteSessionPackedBits(u32 messageId, u32 severity, u32 code);

void ReportContextError(u32 code)
{
    u32 result;
    u32 messageId;

    data_ov031_020bc820->unk_48 = code;
    result = func_ov001_02068084();
    if (result == 2) {
        messageId = 0x3710;
    } else {
        messageId = 0x3718;
    }
    WriteSessionPackedBits(messageId, 6, code);
}
