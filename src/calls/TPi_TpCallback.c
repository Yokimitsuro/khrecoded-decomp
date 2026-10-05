#include "nitro/types.h"

typedef void (*TPRecvCallback)(int command, int result, u16 index);

typedef struct TPData {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TPData;

typedef union SPITpData {
    struct {
        u32 x : 12;
        u32 y : 12;
        u32 touch : 1;
        u32 validity : 2;
        u32 dummy : 5;
    } e;
    u32 raw;
    u16 halfs[2];
} SPITpData;

typedef struct TPState {
    u32 reserved0;
    TPRecvCallback callback;
    TPData buf;
    u16 index;
    u16 frequence;
    TPData *samplingBufs;
    u16 bufSize;
    u16 reserved1a;
    s32 calibrate[6];
    u16 calibrateFlag;
    vu16 state;
    vu16 errorFlags;
    vu16 commandFlags;
} TPState;

extern TPState data_02059784;
extern void OS_Terminate(void);

static inline void CopyTpFromSystemWork(TPData *result)
{
    SPITpData spiTp;

    spiTp.halfs[0] = *(u16 *)0x02ffffaa;
    spiTp.halfs[1] = *(u16 *)0x02ffffac;
    result->x = (u16)spiTp.e.x;
    result->y = (u16)spiTp.e.y;
    result->touch = (u8)spiTp.e.touch;
    result->validity = (u8)spiTp.e.validity;
}

void TPi_TpCallback(int tag, u32 data, BOOL err)
{
    u16 result;
    u16 command;

    result = (u16)(data & 0xffff);
    command = (u16)((result & 0x7f00) >> 8);

    if (err) {
        data_02059784.errorFlags |= (1 << command);
        if (data_02059784.callback) {
            data_02059784.callback(command, 4, 0);
        }
        return;
    }

    if (command == 0x10) {
        data_02059784.index++;
        if (data_02059784.index >= data_02059784.bufSize) {
            data_02059784.index = 0;
        }
        CopyTpFromSystemWork(&data_02059784.samplingBufs[data_02059784.index]);
        if (data_02059784.callback) {
            data_02059784.callback(command, 0, (u8)data_02059784.index);
        }
        return;
    }

    if (!(data & 0x01000000)) {
        return;
    }

    switch ((u8)(result & 0xff)) {
    case 0:
        switch (command) {
        case 0:
            CopyTpFromSystemWork(&data_02059784.buf);
            data_02059784.state = 0;
            break;
        case 1:
            data_02059784.state = 2;
            break;
        case 2:
            data_02059784.state = 0;
            break;
        }
        data_02059784.commandFlags &= ~(1 << command);
        if (data_02059784.callback) {
            data_02059784.callback(command, 0, 0);
        }
        break;
    case 4:
        result = 3;
        goto common;
    case 2:
        result = 1;
        goto common;
    case 3:
        result = 2;
common:
        data_02059784.errorFlags |= (1 << command);
        data_02059784.commandFlags &= ~(1 << command);
        if (data_02059784.callback) {
            data_02059784.callback(command, (int)(result & 0xff), 0);
        }
        break;
    case 1:
    default:
        OS_Terminate();
        return;
    }
}
