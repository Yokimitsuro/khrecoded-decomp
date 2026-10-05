#include "nitro/types.h"

typedef void (*WMCallbackFunc)(void *arg);

#define WM_FIFO_BUF_SIZE        256
#define WM_STATUS_BUF_SIZE      2048
#define WM_API_REQUEST_ACCEPTED 0x8000
#define WM_NUM_OF_PORT          16
#define WM_NUM_OF_CALLBACK      44
#define WM_SIZE_MACADDR         6
#define WM_SIZE_CHILD_SSID      24

enum {
    WM_ERRCODE_SUCCESS = 0,
    WM_ERRCODE_FLASH_ERROR = 19
};

enum {
    WM_APIID_INITIALIZE = 0,
    WM_APIID_END = 2,
    WM_APIID_ENABLE = 3,
    WM_APIID_DISABLE = 4,
    WM_APIID_START_PARENT = 8,
    WM_APIID_START_CONNECT = 12,
    WM_APIID_START_MP = 14,
    WM_APIID_SET_MP_DATA = 15,
    WM_APIID_INDICATION = 128,
    WM_APIID_PORT_SEND = 129,
    WM_APIID_PORT_RECV = 130
};

enum {
    WM_STATECODE_CONNECTED = 7,
    WM_STATECODE_DISCONNECTED = 9,
    WM_STATECODE_MPEND_IND = 11,
    WM_STATECODE_MP_IND = 12,
    WM_STATECODE_DISCONNECTED_FROM_MYSELF = 26
};

typedef struct WMStatus {
    u8 pad_00[0x72];
    u16 mp_recvBufSize;
} WMStatus;

typedef struct WMArm9Buf {
    void *WM7;
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

typedef struct WMCallback {
    u16 apiid;
    u16 errcode;
} WMCallback;

typedef struct WMStartMPCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 reserved;
    u16 *recvBuf;
} WMStartMPCallback;

typedef struct WMStartParentCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u8 macAddress[6];
    u16 aid;
    u16 reason;
    u8 ssid[24];
    u16 parentSize;
    u16 childSize;
} WMStartParentCallback;

typedef struct WMStartConnectCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u16 aid;
    u16 reason;
    u16 reserved;
    u8 macAddress[6];
    u16 parentSize;
    u16 childSize;
} WMStartConnectCallback;

typedef struct WMPortRecvCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 port;
    u16 *recvBuf;
    u16 *data;
    u16 length;
    u16 aid;
    u8 macAddress[6];
    u16 seqNo;
    void *arg;
    u16 myAid;
    u16 connectedAidBitmap;
    u8 ssid[24];
    u16 reason;
    u16 reserved;
    u16 maxSendDataSize;
    u16 maxRecvDataSize;
} WMPortRecvCallback;

typedef struct WMPortSendCallback {
    u16 apiid;
    u16 errcode;
    u8 pad_04[0x18];
    WMCallbackFunc callback;
} WMPortSendCallback;

extern u16 data_020597fc;
#define wmInitialized data_020597fc
#define wm9buf (*(WMArm9Buf **)((u8 *)&data_020597fc + 4))

extern WMPortRecvCallback data_0205985c;

extern void DC_InvalidateRange(void *addr, u32 size);
extern void DC_StoreRange(void *addr, u32 size);
extern void OS_Terminate(void);
extern int ShutdownWireless(void);
extern void Ov105_ClearSharedRequestBit(void);
extern void SNDi_LockMutex(void);
extern void MI_CpuFill8(void *dst, u8 data, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void MIi_CpuClear16(u16 data, void *dst, u32 size);

void WmReceiveFifo(int tag, u32 fifoBufAddress, BOOL err)
{
    WMCallback *callback = (WMCallback *)fifoBufAddress;
    WMArm9Buf *w9b = wm9buf;

    if (err) {
        return;
    }

    DC_InvalidateRange(w9b->fifo7to9, WM_FIFO_BUF_SIZE);
    if (!w9b->scanOnlyFlag) {
        DC_InvalidateRange(w9b->status, WM_STATUS_BUF_SIZE);
    }

    if ((u32)callback != (u32)w9b->fifo7to9) {
        DC_InvalidateRange(callback, WM_FIFO_BUF_SIZE);
    }

    if (callback->apiid >= WM_NUM_OF_CALLBACK) {
        if (callback->apiid == WM_APIID_INDICATION) {
            if (callback->errcode == WM_ERRCODE_FLASH_ERROR) {
                OS_Terminate();
            }
            if (w9b->indCallback != NULL) {
                w9b->indCallback(callback);
            }
        } else if (callback->apiid == WM_APIID_PORT_RECV) {
            WMPortRecvCallback *portRecv = (WMPortRecvCallback *)callback;

            if (w9b->portCallbackTable[portRecv->port] != NULL) {
                portRecv->arg = w9b->portCallbackArgument[portRecv->port];
                portRecv->connectedAidBitmap = (u16)w9b->connectedAidBitmap;
                DC_InvalidateRange(portRecv->recvBuf, w9b->status->mp_recvBufSize);
                w9b->portCallbackTable[portRecv->port](portRecv);
            }
        } else if (callback->apiid == WM_APIID_PORT_SEND) {
            WMPortSendCallback *portSend = (WMPortSendCallback *)callback;

            callback->apiid = WM_APIID_SET_MP_DATA;
            if (portSend->callback != NULL) {
                portSend->callback(portSend);
            }
        }
    } else {
        if (callback->apiid == WM_APIID_START_MP) {
            WMStartMPCallback *startMP = (WMStartMPCallback *)callback;

            if (startMP->state == WM_STATECODE_MPEND_IND || startMP->state == WM_STATECODE_MP_IND) {
                if (startMP->errcode == WM_ERRCODE_SUCCESS) {
                    DC_InvalidateRange(startMP->recvBuf, w9b->status->mp_recvBufSize);
                }
            }
        }

        if (((callback->apiid == WM_APIID_DISABLE || callback->apiid == WM_APIID_END)
                && callback->errcode == WM_ERRCODE_SUCCESS)
            || ((callback->apiid == WM_APIID_ENABLE || callback->apiid == WM_APIID_INITIALIZE)
                && callback->errcode != WM_ERRCODE_SUCCESS)) {
            SNDi_LockMutex();
        }

        if (callback->apiid == WM_APIID_END && callback->errcode == WM_ERRCODE_SUCCESS) {
            WMCallbackFunc endCallback = w9b->CallbackTable[callback->apiid];

            ShutdownWireless();
            if (endCallback != NULL) {
                endCallback(callback);
            }
            return;
        }

        if (w9b->CallbackTable[callback->apiid] != NULL) {
            w9b->CallbackTable[callback->apiid](callback);
            if (!wmInitialized) {
                return;
            }
        }

        if (callback->apiid == WM_APIID_START_PARENT || callback->apiid == WM_APIID_START_CONNECT) {
            u16 state, aid, myAid, reason;
            u8 *macAddress;
            u8 *ssid;
            u16 parentSize, childSize;

            if (callback->apiid == WM_APIID_START_PARENT) {
                WMStartParentCallback *parent = (WMStartParentCallback *)callback;

                state = parent->state;
                aid = parent->aid;
                myAid = 0;
                macAddress = parent->macAddress;
                ssid = parent->ssid;
                reason = parent->reason;
                parentSize = parent->parentSize;
                childSize = parent->childSize;
            } else if (callback->apiid == WM_APIID_START_CONNECT) {
                WMStartConnectCallback *child = (WMStartConnectCallback *)callback;

                state = child->state;
                aid = 0;
                myAid = child->aid;
                macAddress = child->macAddress;
                ssid = NULL;
                reason = child->reason;
                parentSize = child->parentSize;
                childSize = child->childSize;
            }
            if (state == WM_STATECODE_CONNECTED || state == WM_STATECODE_DISCONNECTED
                || state == WM_STATECODE_DISCONNECTED_FROM_MYSELF) {
                u16 port;

                if (state == WM_STATECODE_CONNECTED) {
                    w9b->connectedAidBitmap |= (1 << aid);
                } else {
                    w9b->connectedAidBitmap &= ~(1 << aid);
                }
                w9b->myAid = myAid;

                MI_CpuFill8(&data_0205985c, 0, sizeof(WMPortRecvCallback));
                data_0205985c.apiid = WM_APIID_PORT_RECV;
                data_0205985c.errcode = WM_ERRCODE_SUCCESS;
                data_0205985c.state = state;
                data_0205985c.recvBuf = NULL;
                data_0205985c.data = NULL;
                data_0205985c.length = 0;
                data_0205985c.aid = aid;
                data_0205985c.myAid = myAid;
                data_0205985c.connectedAidBitmap = (u16)w9b->connectedAidBitmap;
                data_0205985c.seqNo = 0xffff;
                data_0205985c.reason = reason;
                MI_CpuCopy8(macAddress, data_0205985c.macAddress, WM_SIZE_MACADDR);
                if (ssid != NULL) {
                    MIi_CpuCopy16(ssid, data_0205985c.ssid, WM_SIZE_CHILD_SSID);
                } else {
                    MIi_CpuClear16(0, data_0205985c.ssid, WM_SIZE_CHILD_SSID);
                }
                data_0205985c.maxSendDataSize = (myAid == 0) ? parentSize : childSize;
                data_0205985c.maxRecvDataSize = (myAid == 0) ? childSize : parentSize;

                for (port = 0; port < WM_NUM_OF_PORT; port++) {
                    data_0205985c.port = port;
                    if (w9b->portCallbackTable[port] != NULL) {
                        data_0205985c.arg = w9b->portCallbackArgument[port];
                        w9b->portCallbackTable[port](&data_0205985c);
                    }
                }
            }
        }
    }

    DC_InvalidateRange(w9b->fifo7to9, WM_FIFO_BUF_SIZE);
    Ov105_ClearSharedRequestBit();

    if ((u32)callback != (u32)w9b->fifo7to9) {
        callback->apiid |= WM_API_REQUEST_ACCEPTED;
        DC_StoreRange(callback, WM_FIFO_BUF_SIZE);
    }
}
