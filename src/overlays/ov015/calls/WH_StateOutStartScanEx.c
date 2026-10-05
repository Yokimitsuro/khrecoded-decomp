#include "nitro/types.h"

typedef struct WMGameInfo {
    u16 magicNumber;
    u8 ver;
    u8 platform;
    u32 ggid;
    u16 tgid;
    u8 userGameInfoLength;
    u8 attribute;
} WMGameInfo;

typedef struct WMBssDesc {
    u16 length;
    u16 rssi;
    u8 bssid[6];
    u8 pad_0a[0x3c - 0xa];
    u16 gameInfoLength;
    u16 otherElementCount;
    WMGameInfo gameInfo;
} WMBssDesc;

typedef struct WMStartScanExCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u16 channelList;
    u8 reserved[2];
    u16 bssDescCount;
    WMBssDesc *bssDesc[16];
} WMStartScanExCallback;

typedef struct WirelessHelper {
    u8 pad_00[2];
    u16 autoConnect;
    u8 pad_04[0x28 - 4];
    void (*otherParentCallback)(u8 *bssid);
    void (*foundCallback)(void *bssDesc);
    u8 pad_30[0x4c - 0x30];
    void (*invalidParentCallback)(u8 *bssid);
    int sysState;
} WirelessHelper;

typedef struct WMParentParam {
    u8 pad_00[8];
    u32 ggid;
} WMParentParam;

extern WirelessHelper data_ov015_0207e980;
extern WMParentParam data_ov015_0207ea20;
extern u8 data_ov015_0207efa0[];
extern u8 data_ov015_0207eb60[];
extern void WH_SetError(int code);
extern void SetPanelTransitionMode(int state);
extern BOOL func_ov015_0207414c(void);
extern BOOL func_ov015_02073e1c(void);
extern void DC_InvalidateRange(void *addr, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void WH_StateOutStartScanEx(void *arg) {
    WMStartScanExCallback *cb = arg;
    int i;
    BOOL found;

    if (cb->errcode != 0) {
        WH_SetError(cb->errcode);
        SetPanelTransitionMode(9);
        return;
    }
    if (data_ov015_0207e980.sysState != 2) {
        data_ov015_0207e980.autoConnect = 0;
        if (!func_ov015_0207414c()) {
            SetPanelTransitionMode(9);
        }
        return;
    }
    switch (cb->state) {
    case 4:
        break;
    case 5:
        if (cb->bssDescCount != 0) {
            DC_InvalidateRange(data_ov015_0207efa0, 0x400);
        }
        found = FALSE;
        for (i = 0; i < cb->bssDescCount && !found; i++) {
            WMBssDesc *bd = cb->bssDesc[i];
            u32 length;
            BOOL valid;
            BOOL sizeOk;
            BOOL lengthOk;
            valid = FALSE;
            sizeOk = FALSE;
            lengthOk = FALSE;
            length = bd->gameInfoLength;
            if (length >= 0x10 && length <= 0x80) {
                lengthOk = TRUE;
            }
            if (lengthOk && length == bd->gameInfo.userGameInfoLength + 0x10) {
                sizeOk = TRUE;
            }
            if (sizeOk && bd->gameInfo.magicNumber == 1) {
                valid = TRUE;
            }
            if (!valid) {
                if (data_ov015_0207e980.invalidParentCallback != NULL) {
                    data_ov015_0207e980.invalidParentCallback(bd->bssid);
                }
                continue;
            }
            if (bd->gameInfo.ggid != data_ov015_0207ea20.ggid) {
                if (data_ov015_0207e980.otherParentCallback != NULL) {
                    data_ov015_0207e980.otherParentCallback(bd->bssid);
                }
                continue;
            }
            if ((bd->gameInfo.attribute & 3) != 1) {
                continue;
            }
            MI_CpuCopy8(bd, data_ov015_0207eb60, 0xc0);
            found = TRUE;
            break;
        }
        if (found) {
            if (data_ov015_0207e980.foundCallback != NULL) {
                data_ov015_0207e980.foundCallback(data_ov015_0207eb60);
            }
            if (data_ov015_0207e980.autoConnect) {
                if (!func_ov015_0207414c()) {
                    SetPanelTransitionMode(9);
                }
                return;
            }
        }
        break;
    }
    if (!func_ov015_02073e1c()) {
        SetPanelTransitionMode(9);
    }
}
