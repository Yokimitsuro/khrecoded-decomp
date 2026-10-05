#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xe0];
    u8 lowBits : 2;
    u8 stateFlag2 : 1;
    u8 midBits : 3;
    u8 stateFlag6 : 1;
    u8 highBit : 1;
    u8 pad_e1;
    u8 lowFlags : 4;
    u8 sharingStarted : 1;
    u8 highFlags : 3;
    u8 pad_e3;
    u32 exitRequest;
    u32 exitTimer;
} PanelState;

typedef struct PlayerCard {
    u8 data[0x70];
} PlayerCard;

extern PanelState *data_ov015_0207e960;
extern u32 SetBusyFlag(void);
extern void InitPlayerCard(PlayerCard *card);
extern void InitShareBuffers(const void *header);
extern void func_ov015_02072cec(void (*callback)(void));
extern void func_ov015_020721ec(void);
extern void func_ov002_020666c8(u32 value);

void StartPlayerCardSharing(void)
{
    PlayerCard card;

    if (!data_ov015_0207e960->sharingStarted) {
        SetBusyFlag();
        InitPlayerCard(&card);
        InitShareBuffers(&card);
        func_ov015_02072cec(func_ov015_020721ec);
        data_ov015_0207e960->sharingStarted = 1;
    }
    data_ov015_0207e960->exitRequest = 0;
    data_ov015_0207e960->exitTimer = 0;
    data_ov015_0207e960->stateFlag6 = 0;
    data_ov015_0207e960->stateFlag2 = 0;
    func_ov002_020666c8(0);
}
