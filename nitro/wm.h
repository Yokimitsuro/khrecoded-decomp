#ifndef NITRO_WM_H
#define NITRO_WM_H

#include "nitro/types.h"

typedef void (*WMCallbackFunc)(void *arg);
typedef int WMErrCode;
typedef int WMApiid;

enum {
    WM_ERRCODE_SUCCESS = 0,
    WM_ERRCODE_FAILED,
    WM_ERRCODE_OPERATING,
    WM_ERRCODE_ILLEGAL_STATE,
    WM_ERRCODE_WM_DISABLE,
    WM_ERRCODE_NO_KEYSET,
    WM_ERRCODE_INVALID_PARAM,
    WM_ERRCODE_NO_CHILD,
    WM_ERRCODE_FIFO_ERROR
};

enum {
    WM_STATE_READY = 0,
    WM_STATE_STOP,
    WM_STATE_IDLE,
    WM_STATE_CLASS1,
    WM_STATE_TESTMODE,
    WM_STATE_SCAN,
    WM_STATE_CONNECT,
    WM_STATE_PARENT,
    WM_STATE_CHILD,
    WM_STATE_MP_PARENT,
    WM_STATE_MP_CHILD
};

enum {
    WM_APIID_INITIALIZE = 0,
    WM_APIID_RESET,
    WM_APIID_END,
    WM_APIID_ENABLE,
    WM_APIID_DISABLE,
    WM_APIID_POWER_ON,
    WM_APIID_POWER_OFF,
    WM_APIID_SET_P_PARAM,
    WM_APIID_START_PARENT,
    WM_APIID_END_PARENT,
    WM_APIID_START_SCAN,
    WM_APIID_END_SCAN,
    WM_APIID_START_CONNECT,
    WM_APIID_DISCONNECT,
    WM_APIID_START_MP,
    WM_APIID_SET_MP_DATA,
    WM_APIID_END_MP,
    WM_APIID_START_DCF,
    WM_APIID_SET_DCF_DATA,
    WM_APIID_END_DCF,
    WM_APIID_SET_WEPKEY,
    WM_APIID_START_KS,
    WM_APIID_END_KS,
    WM_APIID_GET_KEYSET,
    WM_APIID_SET_GAMEINFO,
    WM_APIID_SET_BEACON_IND,
    WM_APIID_START_TESTMODE,
    WM_APIID_STOP_TESTMODE,
    WM_APIID_VALARM_MP,
    WM_APIID_SET_LIFETIME,
    WM_APIID_MEASURE_CHANNEL
};

typedef struct WMStatus {
    u16 state;
    u16 busyApiid;
    BOOL apiBusy;
    BOOL scanContinue;
    BOOL mp_flag;
} WMStatus;

typedef struct WMArm9Buf {
    void *wm7;
    WMStatus *status;
} WMArm9Buf;

typedef struct WMMeasureChannelReq {
    u16 apiid;
    u16 ccaMode;
    u16 edThreshold;
    u16 channel;
    u16 measureTime;
} WMMeasureChannelReq;

#define WM_WEPMODE_NO 0
#define WM_SIZE_WEPKEY 80
#define WMi_CheckState(state) WMi_CheckStateEx(1, (state))
#define WM_CHECK_RESULT(result) \
    if ((result) != WM_ERRCODE_SUCCESS) { return (result); }

#endif
