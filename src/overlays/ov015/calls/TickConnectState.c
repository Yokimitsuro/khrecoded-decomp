#include "nitro/types.h"

typedef struct ConnectState {
    s8 mode;
    s8 result;
    u8 pad_02;
    s8 sendTimer;
    s8 recvTimer;
    u8 pad_05[3];
    u8 card[0x70];
    u8 pad_78;
    u8 sendDone : 1;
    u8 sendPending : 1;
    u8 recvDone : 1;
    u8 recvReset : 1;
    u8 isHost : 1;
    u8 bonusRolled : 1;
    u8 bonusActive : 1;
    u8 bonusKind : 2;
    u8 bonusLocked : 1;
} ConnectState;

typedef struct ConnectModeEntry {
    void (*update)(void);
    u8 pad_04[8];
} ConnectModeEntry;

extern ConnectState *data_ov015_0207e964;
extern ConnectModeEntry gWirelessStateUpdateCallback[];
extern unsigned int func_0202a9e4(unsigned int range);
extern void MI_CpuFill8(void *dest, u8 data, u32 size);

int TickConnectState(void) {
    if (data_ov015_0207e964->sendPending) {
        data_ov015_0207e964->sendTimer = 0;
        data_ov015_0207e964->sendPending = 0;
        data_ov015_0207e964->sendDone = 0;
    } else if (data_ov015_0207e964->sendDone) {
        if (func_0202a9e4(5000) == 100 && !data_ov015_0207e964->bonusLocked && !data_ov015_0207e964->bonusRolled) {
            data_ov015_0207e964->bonusRolled = 1;
            MI_CpuFill8(data_ov015_0207e964->card, 0, 0x70);
            data_ov015_0207e964->bonusKind = 3;
            data_ov015_0207e964->bonusActive = 1;
        }
        data_ov015_0207e964->sendPending = 1;
    }
    data_ov015_0207e964->sendTimer++;
    if (data_ov015_0207e964->sendTimer >= 30) {
        data_ov015_0207e964->sendDone = 1;
    }
    if (data_ov015_0207e964->recvReset) {
        data_ov015_0207e964->recvTimer = 0;
        data_ov015_0207e964->recvReset = 0;
        data_ov015_0207e964->recvDone = 0;
    }
    data_ov015_0207e964->recvTimer++;
    if (data_ov015_0207e964->recvTimer >= 30) {
        data_ov015_0207e964->recvTimer = 30;
        data_ov015_0207e964->recvDone = 1;
    }
    gWirelessStateUpdateCallback[data_ov015_0207e964->mode].update();
    return data_ov015_0207e964->result;
}
