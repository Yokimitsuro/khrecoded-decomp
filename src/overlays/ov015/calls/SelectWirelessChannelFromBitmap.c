typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef void (*WMCallbackFunc)(void *arg);

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0

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
#define OS_MESSAGE_NOBLOCK      0
#define OS_MESSAGE_BLOCK        1
#define MI_DMA_MAX_NUM          3

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
    u16 rsv2[4];
    u16 channel;
    u16 parentMaxSize;
    u16 childMaxSize;
    u16 rsv[4];
} WMParentParam;
#define WM_PARENT_PARAM_SIZE 64

typedef struct WMGameInfo {
    u16 magicNumber;
    u8 ver;
    u8 platform;
    u32 ggid;
    u16 tgid;
    u8 userGameInfoLength;
    u8 attribute;
    u16 parentMaxSize;
    u16 childMaxSize;
    u16 userGameInfo[112 / 2];
} WMGameInfo;

typedef struct WMBssDesc {
    u16 length;
    u16 rssi;
    u8 bssid[6];
    u16 ssidLength;
    u8 ssid[32];
    u16 capaInfo;
    struct { u16 basic; u16 support; } rateSet;
    u16 beaconPeriod;
    u16 dtimPeriod;
    u16 channel;
    u16 cfpPeriod;
    u16 cfpMaxDuration;
    u16 gameInfoLength;
    u16 otherElementCount;
    WMGameInfo gameInfo;
} WMBssDesc;

typedef struct WMScanParam {
    WMBssDesc *scanBuf;
    u16 channel;
    u16 maxChannelTime;
    u8 bssid[6];
    u16 rsv[9];
} WMScanParam;

typedef struct WMStartScanReq {
    u16 apiid;
    u16 channel;
    WMBssDesc *scanBuf;
    u16 maxChannelTime;
    u8 bssid[6];
} WMStartScanReq;

typedef struct WMStartConnectReq {
    u16 apiid;
    u16 reserved;
    WMBssDesc *pInfo;
    u8 ssid[24];
    BOOL powerSave;
    u16 reserved2;
    u16 authMode;
} WMStartConnectReq;

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
    void *mp_recvBuf[2];
    u32 *mp_sendBuf;
    u16 mp_sendBufSize;
    u16 mp_ackTime;
    u16 mp_waitAckFlag;
    u16 mp_readyBitmap;
    u8 reserved88[0x9c - 0x88];
    u16 mp_ignoreSizePrecheckMode;
    u8 reserved9e[0xbc - 0x9e];
    u16 linkLevel;
    u16 minRssi;
    u16 rssiCounter;
    u16 beaconIndicateFlag;
    u16 wepKeyId;
    u16 pwrMgtMode;
    u8 reservedc8[0xe0 - 0xc8];
    u8 MacAddress[6];
    u16 mode;
    WMParentParam pparam;
    u8 childMacAddress[15][6];
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

typedef enum WHSysState {
    WH_SYSSTATE_STOP = 0,
    WH_SYSSTATE_IDLE,
    WH_SYSSTATE_SCANNING,
    WH_SYSSTATE_BUSY,
    WH_SYSSTATE_CONNECTED,
    WH_SYSSTATE_DATASHARING,
    WH_SYSSTATE_KEYSHARING,
    WH_SYSSTATE_MEASURECHANNEL,
    WH_SYSSTATE_CONNECT_FAIL,
    WH_SYSSTATE_ERROR,
    WH_SYSSTATE_FATAL
} WHSysState;

enum {
    WH_CONNECTMODE_MP_PARENT = 0,
    WH_CONNECTMODE_MP_CHILD,
    WH_CONNECTMODE_KS_PARENT,
    WH_CONNECTMODE_KS_CHILD,
    WH_CONNECTMODE_DS_PARENT,
    WH_CONNECTMODE_DS_CHILD
};

enum {
    WM_STATECODE_PARENT_START = 0,
    WM_STATECODE_BEACON_SENT = 2,
    WM_STATECODE_SCAN_START = 3,
    WM_STATECODE_PARENT_NOT_FOUND = 4,
    WM_STATECODE_PARENT_FOUND = 5,
    WM_STATECODE_CONNECT_START = 6,
    WM_STATECODE_CONNECTED = 7,
    WM_STATECODE_BEACON_LOST = 8,
    WM_STATECODE_DISCONNECTED = 9,
    WM_STATECODE_MP_START = 10,
    WM_STATECODE_MPEND_IND = 11,
    WM_STATECODE_MP_IND = 12,
    WM_STATECODE_MPACK_IND = 13,
    WM_STATECODE_PORT_SEND = 20,
    WM_STATECODE_PORT_RECV = 21,
    WM_STATECODE_DISCONNECTED_FROM_MYSELF = 26
};

#define WH_ERRCODE_DISCONNECTED  20
#define WH_ERRCODE_NO_RADIO      22
#define WH_ERRCODE_LOST_PARENT   23
#define WH_ERRCODE_NOMORE_CHANNEL 24
#define WH_DATA_PORT             14
#define WH_DATA_PRIO             2
#define WH_DMA_NO                2
#define WH_BITMAP_EMPTY          0
#define WH_CHANNEL_MAX           16

typedef struct WMCallback {
    u16 apiid;
    u16 errcode;
} WMCallback;

typedef struct WMStartParentCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u8 macAddress[6];
    u16 aid;
    u16 reason;
} WMStartParentCallback;

typedef struct WMStartConnectCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u16 aid;
    u16 reason;
} WMStartConnectCallback;

typedef struct WMStartMPCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
} WMStartMPCallback;

typedef struct WMStartScanCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u16 macAddress[3];
    u16 channel;
    u16 linkLevel;
    u16 ssidLength;
    u16 ssid[16];
    u16 gameInfoLength;
    WMGameInfo gameInfo;
} WMStartScanCallback;
#define WM_SIZE_SYSTEM_GAMEINFO 16
#define WM_GAMEINFO_MAGIC_NUMBER 0x0001
#define WM_ATTR_FLAG_ENTRY 0x01
#define WM_ATTR_FLAG_MB 0x02
static inline BOOL WM_IsValidGameInfo(const WMGameInfo *gameInfo, u16 gameInfoLength)
{
    return (gameInfoLength >= WM_SIZE_SYSTEM_GAMEINFO && gameInfo->magicNumber == WM_GAMEINFO_MAGIC_NUMBER) ? TRUE : FALSE;
}

typedef struct WMMeasureChannelCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 channel;
    u16 ccaBusyRatio;
} WMMeasureChannelCallback;

typedef struct WMPortRecvCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 port;
    u16 restSize;
    u16 reserved;
    u16 *data;
    u16 length;
    u16 aid;
} WMPortRecvCallback;

typedef struct WMPortSendCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 port;
    u16 destBitmap;
    u16 restBitmap;
    u16 sentBitmap;
    u16 reserved;
    u16 *data;
    u16 length;
    u16 seqNo;
    WMCallbackFunc callback;
    void *arg;
    void (*pSendCallback)(BOOL bDelivered);
} WMPortSendCallback;

typedef void (*WhScanCallbackFunc)(WMBssDesc *pBssDesc);
typedef void (*WhReceiverFunc)(u16 nAid, u16 *pData, u16 nSize);
typedef void (*WhSendCallbackFunc)(BOOL bDelivered);
typedef BOOL (*WhJudgeAcceptFunc)(WMStartParentCallback *pCb);
typedef u16 (*WhParentWEPKeyGeneratorFunc)(u16 *pWepKey, const WMParentParam *pParentParam);
typedef u16 (*WhChildWEPKeyGeneratorFunc)(u16 *pWepKey, const WMBssDesc *pBssDesc);

typedef struct WhStatics { u8 opaque00[4]; u16 nChannelBusyRatio; u8 opaque06[6]; u16 nChannelBitmap; u8 opaque0e[0x2a]; u32 nRand; } WhStatics;

extern WhStatics data_ov015_0207e980;
#define sWh data_ov015_0207e980
extern u16 data_ov105_020c0520[16];
extern WMScanParam data_ov105_020c0540;
extern u8 data_ov105_020c0560[24];
extern WMParentParam data_ov105_020c0580;
extern WMBssDesc data_ov105_020c05c0;
#define sWEPKey data_ov105_020c0520
#define sScanParam data_ov105_020c0540
#define sConnectionSsid data_ov105_020c0560
#define sParentParam data_ov105_020c0580
#define sBssDesc data_ov105_020c05c0

extern u16 data_027e0064;
extern u16 data_027e0068;
#define sMyAid data_027e0064
#define sConnectBitmap data_027e0068

extern void func_ov105_020be49c(int nState);
extern void func_ov105_020be4ac(int nError);
#define WH_ChangeSysState func_ov105_020be49c
#define WH_SetError func_ov105_020be4ac

extern WMErrCode func_ov105_020bdea4(WMCallbackFunc callback, u16 aid);
extern WMErrCode func_ov105_020be0fc(WMCallbackFunc callback, u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize, u16 mpFreq);
extern WMErrCode func_ov105_020be164(WMCallbackFunc callback, void *arg, const u16 *sendData, u16 sendDataSize, u16 destBitmap, u16 port, u16 prio);
extern WMErrCode func_ov105_020bd59c(u16 port, WMCallbackFunc callback, void *arg);
extern u16 func_ov105_020bd7a4(void);
extern u16 func_ov105_020bd854(void);
extern WMErrCode func_ov105_020bf480(WMCallbackFunc func, u16 channel);
extern u16 func_ov105_020bf33c(u16 channel);
extern void func_ov105_020bf3d8(void *arg);
extern BOOL func_ov105_020be4c8(void);
extern BOOL func_ov105_020bec64(void);
extern BOOL func_ov105_020becfc(void);
extern BOOL func_ov105_020bee7c(void);
extern void func_ov105_020beee0(void *arg);
extern void func_ov105_020befe0(void *arg);
extern void func_ov105_020bf0e0(void *arg);
extern void func_ov105_020bf120(void *arg);
extern BOOL func_ov105_020bf66c(void);
extern void func_ov105_020bf90c(void);
extern BOOL func_ov105_020beb98(void);
extern BOOL func_ov105_020be850(void);
extern BOOL func_ov105_020bef44(void);
extern void DC_FlushRange(void *addr, u32 size);
extern void DC_WaitWriteBufferEmpty(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 data, u32 size);
#define MI_CpuClear8(dst, size) MI_CpuFill8((dst), 0, (size))
extern void OS_GetMacAddress(u8 *macAddress);
#define OS_GetVBlankCount() (*(volatile u32 *)0x027ffc3c)
extern void *func_020236f8(u32 size, int align, void **heap);
extern void func_02023728(void *ptr, void *heap);
extern void *data_0204c024;
#define WH_RAND_INIT(x) (sWh.nRand = (u32)(x))
#define WH_RAND()       (sWh.nRand = sWh.nRand * 69069UL + 12345)
#define WH_MATH_MIN(a, b) (((a) < (b)) ? (a) : (b))

s16 SelectWirelessChannelFromBitmap(u16 bitmap)
{
    s16 i;
    s16 channel = 0;
    u16 num = 0;
    u16 select;

    for (i = 0; i < 16; i++) {
        if (bitmap & (1 << i)) {
            channel = (s16)(i + 1);
            num++;
        }
    }

    if (num <= 1)
        return channel;

    select = (u16)(((WH_RAND() & 0xFF) * num) / 0x100);

    channel = 1;

    for (i = 0; i < 16; i++) {
        if (bitmap & 1) {
            if (select == 0)
                return (s16)(i + 1);

            select--;
        }
        bitmap >>= 1;
    }

    return 0;
}
