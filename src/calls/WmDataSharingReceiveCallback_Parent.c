#include "nitro/types.h"
#include "nitro/os_types.h"

typedef struct {
    u16 aidBitmap;
    u16 receivedBitmap;
    u16 data[254];
} WMDataSet;

typedef struct {
    WMDataSet ds[4];
    u16 seqNum[4];
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
} WMDataSharingInfo;

typedef struct {
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
} WMPortRecvCallback;

extern void WmDataSharingReceiveData(WMDataSharingInfo *dsInfo, u16 aid, u16 *data);
extern BOOL WmDataSharingSendDataSet(WMDataSharingInfo *dsInfo, BOOL delegate);
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);

void WmDataSharingReceiveCallback_Parent(void *arg) {
    WMPortRecvCallback *cb = (WMPortRecvCallback *)arg;
    WMDataSharingInfo *dsInfo = (WMDataSharingInfo *)cb->arg;

    if (dsInfo) {
        if (cb->errcode == 0) {
            switch (cb->state) {
            case 21:
                WmDataSharingReceiveData(dsInfo, cb->aid, cb->data);
                (void)WmDataSharingSendDataSet(dsInfo, FALSE);
                break;
            case 7:
                (void)WmDataSharingSendDataSet(dsInfo, FALSE);
                break;
            case 25:
                break;
            case 9:
            case 26:
                {
                    OSIntrMode enabled;
                    u32 aidBit = 1U << cb->aid;
                    u16 writeIndex;

                    enabled = OS_DisableInterrupts();
                    writeIndex = dsInfo->writeIndex;
                    dsInfo->ds[writeIndex].aidBitmap &= ~aidBit;
                    if (dsInfo->doubleMode == TRUE) {
                        dsInfo->ds[(u16)((writeIndex + 1) % 4U)].aidBitmap &= ~aidBit;
                    }
                    (void)OS_RestoreInterrupts(enabled);
                    (void)WmDataSharingSendDataSet(dsInfo, FALSE);
                    if (dsInfo->doubleMode == TRUE) {
                        (void)WmDataSharingSendDataSet(dsInfo, FALSE);
                    }
                }
                break;
            }
        } else {
            dsInfo->state = 5;
        }
    }
}
