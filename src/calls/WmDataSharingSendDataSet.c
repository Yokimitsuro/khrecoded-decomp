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

typedef void (*WMCallbackFunc)(void *arg);

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern u16 GetSessionLinkState(void);
extern void MIi_CpuClear16(u16 data, void *dest, u32 size);
extern int WM_SetMPDataToPortEx(WMCallbackFunc callback, void *arg, const u16 *sendData, u16 sendDataSize, u16 destBitmap, u16 port, u16 prio);
extern void WmDataSharingSetDataCallback(void *arg);

void WmDataSharingSendDataSet(WMDataSharingInfo *dsInfo, BOOL delegate) {
    OSIntrMode enabled = OS_DisableInterrupts();

    if (dsInfo->ds[dsInfo->writeIndex].aidBitmap == 0) {
        u16 newWI, oldWI, resetWI;
        int result;
        u16 currentConsole;

        currentConsole = GetSessionLinkState();
        oldWI = dsInfo->writeIndex;
        newWI = (u16)((oldWI + 1) % 4U);
        if (dsInfo->doubleMode == TRUE) {
            resetWI = (u16)((newWI + 1) % 4U);
        } else {
            resetWI = newWI;
        }

        MIi_CpuClear16(0, &dsInfo->ds[resetWI], sizeof(WMDataSet));
        dsInfo->ds[resetWI].aidBitmap = (u16)(dsInfo->aidBitmap & (currentConsole | 0x0001));
        dsInfo->writeIndex = newWI;
        dsInfo->ds[oldWI].aidBitmap = dsInfo->aidBitmap;
        if (delegate == TRUE) {
            dsInfo->ds[oldWI].aidBitmap &= ~0x0001;
        }
        (void)OS_RestoreInterrupts(enabled);
        result = WM_SetMPDataToPortEx(WmDataSharingSetDataCallback, dsInfo, (u16 *)&dsInfo->ds[oldWI],
                                               dsInfo->dataSetLength, (u16)(currentConsole & dsInfo->aidBitmap),
                                               dsInfo->port, 1);
        if (result == 7) {
            dsInfo->seqNum[oldWI] = 0xffff;
            dsInfo->sendIndex = (u16)((dsInfo->sendIndex + 1) % 4U);
        } else if (result != 0 && result != 2) {
            dsInfo->state = 5;
        }
    } else {
        (void)OS_RestoreInterrupts(enabled);
    }
}
