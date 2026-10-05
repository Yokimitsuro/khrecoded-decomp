#ifndef KH_RECODED_OV001_PANEL_STATE_H
#define KH_RECODED_OV001_PANEL_STATE_H

#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x38];
    BOOL sessionActive;
    u8 pad_3c[4];
    BOOL inputActive;
    BOOL fallbackRequested;
    u8 pad_48[4];
    BOOL brightnessRestoreRequested;
} PanelState;

extern PanelState *data_ov001_020a04e8;

#endif
