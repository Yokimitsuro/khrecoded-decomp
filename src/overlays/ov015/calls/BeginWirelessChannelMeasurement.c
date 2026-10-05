typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct WirelessChannelState {
    u8 unknown00[4];
    u16 minimumOccupancy;
    u16 selectedChannel;
    u8 unknown08[4];
    u16 tiedChannels;
    u8 unknown0e[0x2a];
    u32 randomState;
} WirelessChannelState;
extern WirelessChannelState data_ov015_0207e980;
extern void SetPanelTransitionMode(int state);
extern void OS_GetMacAddress(u8 *address);
extern void WH_SetError(int result);
extern u16 measure_next_allowed_wireless_channel(u16 channel);
static inline u32 ReadFrameCounter(void) {
    return *(volatile u32 *)0x02fffc3c;
}
int BeginWirelessChannelMeasurement(void) {
    u16 mac[3];
    u16 result;
    OS_GetMacAddress((u8 *)mac);
    data_ov015_0207e980.randomState = (((mac[0] + ReadFrameCounter()) + mac[1]) + mac[2]) * 69069U + 12345U;
    data_ov015_0207e980.selectedChannel = 0;
    data_ov015_0207e980.minimumOccupancy = 101;
    SetPanelTransitionMode(3);
    result = measure_next_allowed_wireless_channel(1);
    if (result == 24) {
        WH_SetError(24);
        SetPanelTransitionMode(9);
        return 0;
    }
    if (result == 2) return 1;
    WH_SetError(result);
    SetPanelTransitionMode(9);
    return 0;
}
