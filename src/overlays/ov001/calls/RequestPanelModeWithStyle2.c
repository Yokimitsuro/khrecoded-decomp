#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x108];
    u32 sessionFlags;
} PanelScene;

extern PanelScene *data_ov001_020a04e8;
extern BOOL RequestPanelModeChange(int mode);

BOOL RequestPanelModeWithStyle2(int mode)
{
    data_ov001_020a04e8->sessionFlags = 2;
    return RequestPanelModeChange(mode);
}
