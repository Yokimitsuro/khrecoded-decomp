#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x24];
    int sendBufferSize;
    u8 pad_28[0x14];
    int recvBufferSize;
    int connectMode;
} WirelessHelperState;

typedef struct ParentParam {
    void *userGameInfo;
    u16 userGameInfoLength;
    u16 padding;
    u32 ggid;
    u16 tgid;
    u16 entryFlag;
    u16 maxEntry;
    u16 multiBootFlag;
    u16 keySharingFlag;
    u16 continuousSendFlag;
    u16 beaconPeriod;
    u16 reserved1[4];
    u16 reserved2[8];
    u16 channel;
    u16 parentMaxSize;
    u16 childMaxSize;
} ParentParam;

extern WirelessHelperState data_ov015_0207e980;
extern ParentParam data_ov015_0207ea20;
extern void SetPanelTransitionMode(int state);
extern u16 GetDispersionBeaconPeriod(void);
extern BOOL func_ov015_020737f0(void);

BOOL WH_ParentConnect(int mode, u16 tgid, u16 channel)
{
    data_ov015_0207e980.recvBufferSize = 0x380;
    data_ov015_0207e980.sendBufferSize = 0xa0;
    data_ov015_0207e980.connectMode = mode;
    SetPanelTransitionMode(3);
    data_ov015_0207ea20.tgid = tgid;
    data_ov015_0207ea20.channel = channel;
    data_ov015_0207ea20.beaconPeriod = GetDispersionBeaconPeriod();
    data_ov015_0207ea20.parentMaxSize = 0x84;
    data_ov015_0207ea20.childMaxSize = 0x80;
    data_ov015_0207ea20.maxEntry = 3;
    data_ov015_0207ea20.continuousSendFlag = 0;
    data_ov015_0207ea20.multiBootFlag = 0;
    data_ov015_0207ea20.entryFlag = 1;
    data_ov015_0207ea20.keySharingFlag = (u16)(mode == 2 ? TRUE : FALSE);
    switch (mode) {
    case 0:
    case 2:
    case 4:
        return func_ov015_020737f0();
    default:
        break;
    }
    return FALSE;
}
