#include "nitro/types.h"

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

extern u16 GetSessionChannel(void);
extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);

void WmDataSharingReceiveCallback_Child(void *arg)
{
    WMPortRecvCallback *cb = (WMPortRecvCallback *)arg;
    WMDataSharingInfo *dsInfo = (WMDataSharingInfo *)cb->arg;

    if (dsInfo) {
        if (cb->errcode == 0) {
            switch (cb->state) {
            case 21:
                {
                    WMDataSet *dataSet = (WMDataSet *)cb->data;
                    u16 length = cb->length;
                    u16 aidBitmap = dataSet->aidBitmap;
                    u16 aid = GetSessionChannel();

                    if (length != dsInfo->dataSetLength) {
                        if (length > sizeof(WMDataSet)) {
                            length = sizeof(WMDataSet);
                        }
                    }
                    if (length < 4) {
                        break;
                    }
                    if (!(aidBitmap & (1 << aid))) {
                        break;
                    }
                    MIi_CpuCopy16(dataSet, &dsInfo->ds[dsInfo->writeIndex], length);
                    dsInfo->seqNum[dsInfo->writeIndex] = (u16)(cb->seqNo >> 1);
                    dsInfo->writeIndex = (u16)((dsInfo->writeIndex + 1) % 4U);
                }
                break;
            case 7:
            case 9:
            case 25:
            case 26:
                break;
            }
        } else {
            dsInfo->state = 5;
        }
    }
}
