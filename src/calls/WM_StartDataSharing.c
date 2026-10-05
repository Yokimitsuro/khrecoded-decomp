#include "nitro/types.h"

typedef void (*WMCallbackFunc)(void *arg);

#define WM_NUM_OF_PORT      16
#define WM_DS_DATASET_NUM   4
#define WM_DS_DATASET_SIZE  0x1fc
#define WM_DS_HEADER_SIZE   4
#define WM_PRIORITY_HIGH    1

enum {
    WM_ERRCODE_SUCCESS = 0,
    WM_ERRCODE_FAILED = 1,
    WM_ERRCODE_OPERATING = 2,
    WM_ERRCODE_INVALID_PARAM = 6,
    WM_ERRCODE_NO_CHILD = 7
};

enum {
    WM_STATE_MP_PARENT = 9,
    WM_STATE_MP_CHILD = 10
};

enum {
    WM_DS_STATE_READY = 0,
    WM_DS_STATE_START = 1,
    WM_DS_STATE_ERROR = 5
};

typedef struct WMDataSet {
    u16 aidBitmap;
    u16 receivedBitmap;
    u16 data[254];
} WMDataSet;

typedef struct WMDataSharingInfo {
    WMDataSet ds[WM_DS_DATASET_NUM];
    u16 seqNum[WM_DS_DATASET_NUM];
    u16 writeIndex;
    u16 sendIndex;
    u16 readIndex;
    u16 aidBitmap;
    u16 dataLength;
    u16 stationNumber;
    u16 dataSetLength;
    u16 port;
    u16 doubleMode;
    u16 currentSeqNum;
    u16 state;
    u16 reserved;
} WMDataSharingInfo;

extern int WMi_CheckStateEx(s32 paramNum, ...);
extern int GetSessionChannel(void);
extern u16 GetSessionLinkState(void);
extern void MIi_CpuClearFast(int data, void *dst, int size);
extern u32 PopCount32(u32 bits);
extern int SetSlotEventHandler(int port, WMCallbackFunc callback, void *arg);
extern int WM_SetMPDataToPortEx(WMCallbackFunc callback, void *arg, const u16 *sendData, u16 sendDataSize, u16 destBitmap, u16 port, u16 prio);
extern void WmDataSharingSetDataCallback(void *arg);
extern void func_02011f7c(void *arg);
extern void WmDataSharingReceiveCallback_Child(void *arg);

int WM_StartDataSharing(WMDataSharingInfo *dsInfo, u16 port, u16 aidBitmap, u16 dataLength, BOOL doubleMode)
{
    int result;
    int aid;
    u32 connectedAidBitmap = 1;

    result = WMi_CheckStateEx(2, WM_STATE_MP_PARENT, WM_STATE_MP_CHILD);
    if (result != WM_ERRCODE_SUCCESS) {
        return result;
    }

    if (dsInfo == NULL) {
        return WM_ERRCODE_INVALID_PARAM;
    }
    if (port >= WM_NUM_OF_PORT) {
        return WM_ERRCODE_INVALID_PARAM;
    }
    if (aidBitmap == 0) {
        return WM_ERRCODE_INVALID_PARAM;
    }

    aid = GetSessionChannel();
    if (aid == 0) {
        connectedAidBitmap = GetSessionLinkState();
    }

    MIi_CpuClearFast(0, dsInfo, sizeof(WMDataSharingInfo));
    dsInfo->writeIndex = 0;
    dsInfo->sendIndex = 0;
    dsInfo->readIndex = 0;
    dsInfo->dataLength = dataLength;
    dsInfo->port = port;
    dsInfo->aidBitmap = 0;
    dsInfo->doubleMode = doubleMode ? TRUE : FALSE;

    aidBitmap |= (u16)(1 << aid);
    dsInfo->aidBitmap = aidBitmap;
    {
        u32 count = PopCount32(aidBitmap);

        dsInfo->stationNumber = count;
        dsInfo->dataSetLength = (u16)(dataLength * count);
        if (dsInfo->dataSetLength > WM_DS_DATASET_SIZE) {
            dsInfo->aidBitmap = 0;
            return WM_ERRCODE_INVALID_PARAM;
        }
        dsInfo->dataSetLength += WM_DS_HEADER_SIZE;
    }

    dsInfo->state = WM_DS_STATE_START;

    if (aid == 0) {
        int i;

        for (i = 0; i < WM_DS_DATASET_NUM; i++) {
            dsInfo->ds[i].aidBitmap = (u16)(dsInfo->aidBitmap & (connectedAidBitmap | 1));
        }

        SetSlotEventHandler(port, func_02011f7c, dsInfo);

        for (i = 0; i < ((dsInfo->doubleMode == TRUE) ? 2 : 1); i++) {
            int sendResult;
            WMDataSet *dataSet = &dsInfo->ds[i];

            dsInfo->writeIndex = (u16)((dsInfo->writeIndex + 1) & (WM_DS_DATASET_NUM - 1));
            sendResult = WM_SetMPDataToPortEx(WmDataSharingSetDataCallback, dsInfo, (u16 *)dataSet,
                dsInfo->dataSetLength, (u16)(connectedAidBitmap & dsInfo->aidBitmap), dsInfo->port,
                WM_PRIORITY_HIGH);
            if (sendResult == WM_ERRCODE_NO_CHILD) {
                dsInfo->seqNum[i] = 0xffff;
                dsInfo->sendIndex = (u16)((dsInfo->sendIndex + 1) & (WM_DS_DATASET_NUM - 1));
            } else if (sendResult != WM_ERRCODE_SUCCESS && sendResult != WM_ERRCODE_OPERATING) {
                dsInfo->state = WM_DS_STATE_ERROR;
                return WM_ERRCODE_FAILED;
            }
        }
    } else {
        dsInfo->sendIndex = WM_DS_DATASET_NUM - 1;
        SetSlotEventHandler(port, WmDataSharingReceiveCallback_Child, dsInfo);
    }

    return WM_ERRCODE_SUCCESS;
}
