#include "nitro/types.h"

typedef struct {
    void *data;
    int size;
} SessionBuffer;

typedef struct {
    u8 pad_0000[8];
    void *heapB;
    u8 pad_000c[4];
    int overlayId;
    u8 pad_0014[4];
    s8 overlaySlot;
    u8 pad_0019[0x1f0c - 0x19];
    void *scratch;
    u8 pad_1f10[0x272c - 0x1f10];
    void *halfBuffer;
    u8 pad_2730[0xc];
    void *workBuffer;
    void *heapA;
    u8 pad_2744[0x27f2 - 0x2744];
    s8 entryCount;
    u8 pad_27f3;
    void **entries;
    u8 pad_27f8[0x283c - 0x27f8];
    SessionBuffer buffers[13];
} Session;

extern void *data_ov001_020a0480;
extern Session *NNSi_FndGetCurrentRootHeap(void);
extern void ShutdownSessionOverlays(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_02029fac(int processor, int overlayId);
extern int ZeroHalfThenFree(void *block);
extern void PXI_Init_0202a64c(void *heap);
extern void ShutdownPanelState(void);
extern void func_ov001_02066e18(void);
extern void func_ov001_02066454(void);
extern void DestroyFieldObjectManager(void);
extern void func_ov001_02069214(void);
extern void ReleaseServiceInstance_020690ac(void);
extern void func_ov001_020685a4(void);
extern void ReleaseServiceInstance(void);
extern void func_ov001_02069508(void);
extern void func_ov001_0206747c(void);
extern void DeferredDraw_Release(void);
extern void ShutdownActorRegistry(void);
extern void func_ov001_02063c54(void);
extern void TP_RequestAutoSamplingStopAsync(void);
extern void TP_WaitBusy(unsigned int mask);
extern int TP_CheckError(int mask);
extern void ReleaseRecordManager(void);
extern void LoadSeqArcIfChanged(int seqArcNo);
extern void func_02050a58(void);

void ShutdownFieldSession(void)
{
    Session *session = NNSi_FndGetCurrentRootHeap();
    int i;

    ShutdownSessionOverlays();
    for (i = 0; i < 13; i++) {
        if (session->buffers[i].data != NULL) {
            NNSi_FndFreeFromDefaultHeap(session->buffers[i].data);
        }
    }
    if (session->overlayId != -1) {
        func_02029fac(0, session->overlayId);
        session->overlayId = -1;
        session->overlaySlot = -1;
    }
    if (session->entries != NULL) {
        for (i = 0; i < session->entryCount; i++) {
            if (session->entries[i] != NULL) {
                NNSi_FndFreeFromDefaultHeap(session->entries[i]);
            }
        }
        NNSi_FndFreeFromDefaultHeap(session->entries);
    }
    if (session->workBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(session->workBuffer);
    }
    if (session->halfBuffer != NULL) {
        ZeroHalfThenFree(session->halfBuffer);
    }
    PXI_Init_0202a64c(session->heapA);
    PXI_Init_0202a64c(session->heapB);
    ShutdownPanelState();
    func_ov001_02066e18();
    func_ov001_02066454();
    DestroyFieldObjectManager();
    func_ov001_02069214();
    ReleaseServiceInstance_020690ac();
    func_ov001_020685a4();
    ReleaseServiceInstance();
    func_ov001_02069508();
    func_ov001_0206747c();
    DeferredDraw_Release();
    ShutdownActorRegistry();
    func_ov001_02063c54();
    TP_RequestAutoSamplingStopAsync();
    TP_WaitBusy(4);
    TP_CheckError(4);
    ReleaseRecordManager();
    LoadSeqArcIfChanged(0);
    func_02050a58();
    if (session->scratch != NULL) {
        NNSi_FndFreeFromDefaultHeap(session->scratch);
        session->scratch = NULL;
    }
    data_ov001_020a0480 = NULL;
}
