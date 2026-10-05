#include "nitro/types.h"

extern void MarkCommChannelBusy(void); /* MarkCommChannelBusy */
extern void SyncSessionCommFlags(void); /* SyncSessionCommFlags */
extern void func_ov037_020ba810(void); /* FinishCommSession */
extern void NotifyCommSlotIfReady(void); /* NotifyCommSlotIfReady */
extern void ResetCommSlotWhenIdle(void); /* ResetCommSlotWhenIdle */
extern void StoreCommResultSlot(void); /* StoreCommResultSlot */
extern void func_ov037_020ba92c(void);
extern void AdvanceCommWhenReady(void); /* AdvanceCommWhenReady */
extern void MarkCommBusyWhenReady(void); /* MarkCommBusyWhenReady */
extern void func_ov037_020ba9a0(void); /* CloseCommAndRestoreRoom */
extern void func_ov037_020baa5c(void);

void (*gCommunicationStateHandlers[11])(void) = {
    MarkCommChannelBusy, /* MarkCommChannelBusy */
    SyncSessionCommFlags, /* SyncSessionCommFlags */
    func_ov037_020ba810, /* FinishCommSession */
    NotifyCommSlotIfReady, /* NotifyCommSlotIfReady */
    ResetCommSlotWhenIdle, /* ResetCommSlotWhenIdle */
    StoreCommResultSlot, /* StoreCommResultSlot */
    func_ov037_020ba92c,
    AdvanceCommWhenReady, /* AdvanceCommWhenReady */
    MarkCommBusyWhenReady, /* MarkCommBusyWhenReady */
    func_ov037_020ba9a0, /* CloseCommAndRestoreRoom */
    func_ov037_020baa5c,
};
