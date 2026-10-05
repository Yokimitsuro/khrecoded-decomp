#include "nitro/types.h"

typedef struct ConnectState {
    s8 slot;
    u8 count;
    u8 receiving;
    u8 pad_03[5];
    u8 peerCard[0x70];
    u8 peerAid;
    u8 lowFlag : 1;
    u8 exchangeStarted : 1;
    u8 midFlags : 3;
    u8 peerKnown : 1;
    u8 peerReady : 1;
    u8 highFlag : 1;
    u8 exchangeStep : 2;
    u8 otherFlags : 6;
    u8 pad_7b[5];
    int received[5];
    void *sendBuffer;
    void *recvBuffers[4];
} ConnectState;

extern ConnectState *data_ov015_0207e964;
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void ReceiveChildCardData(int aid, u8 *data)
{
    data_ov015_0207e964->receiving = 0;
    if (data != NULL) {
        if (!data_ov015_0207e964->peerKnown) {
            data_ov015_0207e964->received[aid] = 1;
            if (aid != 0) {
                data_ov015_0207e964->peerKnown = 1;
                data_ov015_0207e964->exchangeStep = 0;
                data_ov015_0207e964->peerAid = aid;
                MI_CpuCopy8(data, data_ov015_0207e964->recvBuffers[aid], 0x80);
                MI_CpuCopy8(data, data_ov015_0207e964->peerCard, 0x70);
                data_ov015_0207e964->peerReady = 1;
            }
        }
    } else {
        data_ov015_0207e964->received[aid] = 0;
    }
}
