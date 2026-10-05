#include "nitro/types.h"
#include "nitro/mi.h"
#include "nitro/os.h"

typedef void (*WMCallbackFunc)(void *arg);

#define WM_FIFO_BUF_SIZE        256
#define WM_ARM9WM_BUF_SIZE      512
#define WM_ARM7WM_BUF_SIZE      (256 + 512)
#define WM_STATUS_BUF_SIZE      2048
#define WM_API_REQUEST_ACCEPTED 0x8000
#define WM_NUM_OF_PORT          16
#define WM_NUM_OF_CALLBACK      44
#define WM_BUF_MSG_NUM          10
#define PXI_FIFO_TAG_WM         10
#define PXI_PROC_ARM7           1

enum {
    WM_ERRCODE_SUCCESS = 0,
    WM_ERRCODE_FAILED = 1,
    WM_ERRCODE_OPERATING = 2,
    WM_ERRCODE_ILLEGAL_STATE = 3,
    WM_ERRCODE_WM_DISABLE = 4,
    WM_ERRCODE_NO_KEYSET = 5,
    WM_ERRCODE_INVALID_PARAM = 6,
    WM_ERRCODE_NO_CHILD = 7,
    WM_ERRCODE_FIFO_ERROR = 8,
    WM_ERRCODE_TIMEOUT = 9,
    WM_ERRCODE_SEND_QUEUE_FULL = 10,
    WM_ERRCODE_NO_ENTRY = 11,
    WM_ERRCODE_OVER_MAX_ENTRY = 12,
    WM_ERRCODE_INVALID_POLLBITMAP = 13,
    WM_ERRCODE_NO_DATA = 14,
    WM_ERRCODE_SEND_FAILED = 15
};
typedef int WMErrCode;

enum {
    WM_STATE_READY = 0, WM_STATE_STOP, WM_STATE_IDLE, WM_STATE_CLASS1, WM_STATE_TESTMODE,
    WM_STATE_SCAN, WM_STATE_CONNECT, WM_STATE_PARENT, WM_STATE_CHILD, WM_STATE_MP_PARENT,
    WM_STATE_MP_CHILD, WM_STATE_DCF_CHILD, WM_STATE_TESTMODE_RX
};

enum {
    WM_APIID_INITIALIZE = 0, WM_APIID_RESET, WM_APIID_END, WM_APIID_ENABLE, WM_APIID_DISABLE,
    WM_APIID_POWER_ON, WM_APIID_POWER_OFF, WM_APIID_SET_P_PARAM, WM_APIID_START_PARENT,
    WM_APIID_END_PARENT, WM_APIID_START_SCAN, WM_APIID_END_SCAN, WM_APIID_START_CONNECT,
    WM_APIID_DISCONNECT, WM_APIID_START_MP, WM_APIID_SET_MP_DATA, WM_APIID_END_MP,
    WM_APIID_START_DCF, WM_APIID_SET_DCF_DATA, WM_APIID_END_DCF, WM_APIID_SET_WEPKEY,
    WM_APIID_START_KS, WM_APIID_END_KS, WM_APIID_GET_KEYSET, WM_APIID_SET_GAMEINFO,
    WM_APIID_SET_BEACON_IND, WM_APIID_START_TESTMODE, WM_APIID_STOP_TESTMODE,
    WM_APIID_VALARM_MP, WM_APIID_SET_LIFETIME, WM_APIID_MEASURE_CHANNEL,
    WM_APIID_INIT_W_COUNTER, WM_APIID_GET_W_COUNTER, WM_APIID_SET_ENTRY, WM_APIID_AUTO_DEAUTH,
    WM_APIID_SET_MP_PARAMETER, WM_APIID_SET_BEACON_PERIOD, WM_APIID_AUTO_DISCONNECT,
    WM_APIID_START_SCAN_EX, WM_APIID_SET_WEPKEY_EX, WM_APIID_SET_PS_MODE,
    WM_APIID_START_TESTRXMODE, WM_APIID_STOP_TESTRXMODE, WM_APIID_KICK_MP_PARENT,
    WM_APIID_KICK_MP_CHILD, WM_APIID_ASYNC_KIND_MAX,
    WM_APIID_INDICATION = 128, WM_APIID_PORT_SEND, WM_APIID_PORT_RECV, WM_APIID_READ_STATUS
};
typedef int WMApiid;

typedef struct WMParentParam {
    u16 *userGameInfo;
    u16 userGameInfoLength;
    u16 padding;
    u32 ggid;
    u16 tgid;
    u16 entryFlag;
    u16 maxEntry;
    u16 multiBootFlag;
    u16 KS_Flag;
    u16 CS_Flag;
    u16 beaconPeriod;
    u16 rsv1[8];
    u16 rsv2[16];
    u16 channel;
    u16 parentMaxSize;
    u16 childMaxSize;
    u16 rsv[4];
} WMParentParam;

typedef struct WMStatus {
    u16 state;
    u16 BusyApiid;
    BOOL apiBusy;
    BOOL scan_continue;
    BOOL mp_flag;
    BOOL dcf_flag;
    BOOL ks_flag;
    BOOL dcf_sendFlag;
    BOOL VSyncFlag;
    u8 wlVersion[8];
    u16 macVersion;
    u16 rfVersion;
    u16 bbpVersion[2];
    u16 mp_parentSize;
    u16 mp_childSize;
    u16 mp_parentMaxSize;
    u16 mp_childMaxSize;
    u16 mp_sendSize;
    u16 mp_recvSize;
    u16 mp_maxSendSize;
    u16 mp_maxRecvSize;
    u8 reserved40[0x72 - 0x40];
    u16 mp_recvBufSize;
    u8 reserved74[0xbc - 0x74];
    u16 linkLevel;
    u8 reservedbe[0xe0 - 0xbe];
    u8 MacAddress[6];
    u16 mode;
    WMParentParam pparam;
    u8 childMacAddress[0x182 - 0x140];
    u16 child_bitmap;
    void *pInfoBuf;
    u16 aid;
    u8 parentMacAddress[6];
    u16 scan_channel;
    u8 reserved192[0x800 - 0x192];
} WMStatus;

typedef struct WMArm7Buf {
    WMStatus *status;
    u8 reserved_a[4];
    u32 *fifo7to9;
    u8 reserved_b[0x2f4];
} WMArm7Buf;

typedef struct WMArm9Buf {
    WMArm7Buf *WM7;
    WMStatus *status;
    u32 *indbuf;
    u32 *fifo9to7;
    u32 *fifo7to9;
    u16 dmaNo;
    u16 scanOnlyFlag;
    WMCallbackFunc CallbackTable[WM_NUM_OF_CALLBACK];
    WMCallbackFunc indCallback;
    WMCallbackFunc portCallbackTable[WM_NUM_OF_PORT];
    void *portCallbackArgument[WM_NUM_OF_PORT];
    u32 connectedAidBitmap;
    u16 myAid;
} WMArm9Buf;

typedef struct WMMpRecvBuf {
    u16 rsv1[3];
    u16 length;
    u16 rsv2[1];
    u16 ackTimeStamp;
    u16 timeStamp;
    u16 rate_rssi;
    u16 rsv3[2];
    u16 rsv4[2];
    u8 destAdrs[6];
    u8 srcAdrs[6];
    u16 rsv5[3];
    u16 seqCtrl;
    u16 txop;
    u16 bitmap;
    u16 wmHeader;
    u16 data[2];
} WMMpRecvBuf;

typedef struct WMMpRecvData {
    u16 length;
    u16 rate_rssi;
    u16 aid;
    u16 noResponse;
    u16 wmHeader;
    u16 cdata[1];
} WMMpRecvData;

typedef struct WMMpRecvHeader {
    u16 bitmap;
    u16 errBitmap;
    u16 count;
    u16 length;
    u16 txCount;
    WMMpRecvData data[1];
} WMMpRecvHeader;

extern u16 data_ov105_020bfa20;
#define wmInitialized data_ov105_020bfa20
#define wm9buf (*(WMArm9Buf **)((u8 *)&data_ov105_020bfa20 + 4))

extern WMArm9Buf *func_02011050(void);
extern WMErrCode Ov105_IsDeviceReady(void);
extern WMErrCode WMi_CheckStateEx(s32 paramNum, ...);
extern WMErrCode Ov105_WMi_SendCommand(WMApiid id, u16 paramNum, ...);
extern void Ov105_SetCommandArg(WMApiid id, WMCallbackFunc callback);
extern void DC_InvalidateRange(void *addr, u32 size);
extern void OS_GetMacAddress(u8 *macAddress);
#define WM_DEFAULT_BEACON_PERIOD 200
#define WM_DEFAULT_SCAN_PERIOD 30

int WM_GetMPSendBufferSize(void)
{
    WMErrCode result;
    int maxSendSize;
    WMArm9Buf *p = func_02011050();

    result = WMi_CheckStateEx(2, WM_STATE_PARENT, WM_STATE_CHILD);
    if (result != WM_ERRCODE_SUCCESS) {
        return 0;
    }

    DC_InvalidateRange(&(p->status->mp_flag), 4);
    if (p->status->mp_flag == TRUE) {
        return 0;
    }

    DC_InvalidateRange(&(p->status->mp_maxSendSize), 4);
    maxSendSize = p->status->mp_maxSendSize;

    return ((maxSendSize + 31) & ~0x1f);
}
