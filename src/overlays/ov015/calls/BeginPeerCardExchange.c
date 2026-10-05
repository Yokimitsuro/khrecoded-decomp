#include "nitro/types.h"

typedef struct ConnectState {
    u8 pad_00[0x08];
    u8 peerCard[0x5e];
    u8 peerMac[6];
    u8 pad_6c[0xd];
    u8 lowFlag : 1;
    u8 exchangeStarted : 1;
    u8 midFlags : 3;
    u8 peerKnown : 1;
    u8 peerReady : 1;
    u8 highFlag : 1;
    u8 exchangeStep : 2;
    u8 otherFlags : 6;
} ConnectState;

extern ConnectState *data_ov015_0207e964;
extern BOOL IsKnownMacAddress(u8 *macAddress);
extern void MI_CpuFill8(void *dest, u8 data, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void BeginPeerCardExchange(u8 *macAddress)
{
    if (data_ov015_0207e964->peerKnown) {
        return;
    }
    if (IsKnownMacAddress(macAddress)) {
        return;
    }
    data_ov015_0207e964->peerKnown = 1;
    data_ov015_0207e964->exchangeStarted = 1;
    data_ov015_0207e964->exchangeStep = 2;
    MI_CpuFill8(data_ov015_0207e964->peerCard, 0, 0x70);
    MI_CpuCopy8(macAddress, data_ov015_0207e964->peerMac, 6);
    data_ov015_0207e964->peerReady = 1;
}
