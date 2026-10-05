#include "nitro/types.h"

typedef void (*WMCallbackFunc)(void *arg);
typedef int WMErrCode;

typedef struct {
    void *scanBuf;
    u16 scanBufSize;
    u16 channelList;
    u16 maxChannelTime;
    u8 bssid[6];
    u16 scanType;
    u16 ssidLength;
    u8 ssid[32];
    u16 ssidMatchLength;
    u16 rsv[2];
} WMScanExParam;

typedef struct {
    u16 apiid;
    u16 channelList;
    void *scanBuf;
    u16 scanBufSize;
    u16 maxChannelTime;
    u8 bssid[6];
    u16 scanType;
    u16 ssidLength;
    u8 ssid[32];
    u16 ssidMatchLength;
    u16 rsv2[2];
} WMStartScanExReq;

extern WMErrCode WMi_CheckStateEx(s32 paramNum, ...);
extern void SetCommandArg(int apiid, WMCallbackFunc callback);
extern WMErrCode WMi_SendCommandDirect(void *data, u32 length);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

WMErrCode WM_StartScanEx(WMCallbackFunc callback, const WMScanExParam *param)
{
    WMErrCode result;

    result = WMi_CheckStateEx(3, 2, 3, 5);
    if (result != 0) {
        return result;
    }

    if (param == NULL) {
        return 6;
    }
    if (param->scanBuf == NULL) {
        return 6;
    }
    if (param->scanBufSize > 0x400) {
        return 6;
    }
    if (param->ssidLength > 32) {
        return 6;
    }
    if (param->scanType != 0 && param->scanType != 1 && param->scanType != 2 && param->scanType != 3) {
        return 6;
    }
    if ((param->scanType == 2 || param->scanType == 3) && param->ssidMatchLength > 32) {
        return 6;
    }

    SetCommandArg(0x26, callback);

    {
        WMStartScanExReq Req;

        Req.apiid = 0x26;
        Req.channelList = param->channelList;
        Req.scanBuf = param->scanBuf;
        Req.scanBufSize = param->scanBufSize;
        Req.maxChannelTime = param->maxChannelTime;
        MI_CpuCopy8(param->bssid, Req.bssid, 6);
        Req.scanType = param->scanType;
        Req.ssidMatchLength = param->ssidMatchLength;
        Req.ssidLength = param->ssidLength;
        MI_CpuCopy8(param->ssid, Req.ssid, 32);

        result = WMi_SendCommandDirect(&Req, sizeof(Req));
        if (result != 0) {
            return result;
        }
    }

    return 2;
}
