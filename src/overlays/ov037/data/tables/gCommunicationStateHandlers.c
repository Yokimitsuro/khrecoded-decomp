#include "nitro/types.h"

extern void func_ov037_020ba75c(void); /* MarkCommChannelBusy */
extern void func_ov037_020ba784(void); /* SyncSessionCommFlags */
extern void func_ov037_020ba810(void); /* FinishCommSession */
extern void func_ov037_020ba894(void); /* NotifyCommSlotIfReady */
extern void func_ov037_020ba8c8(void); /* ResetCommSlotWhenIdle */
extern void func_ov037_020ba904(void); /* StoreCommResultSlot */
extern void func_ov037_020ba92c(void);
extern void func_ov037_020ba93c(void); /* AdvanceCommWhenReady */
extern void func_ov037_020ba964(void); /* MarkCommBusyWhenReady */
extern void func_ov037_020ba9a0(void); /* CloseCommAndRestoreRoom */
extern void func_ov037_020baa5c(void);

void (*gCommunicationStateHandlers[11])(void) = {
    func_ov037_020ba75c, /* MarkCommChannelBusy */
    func_ov037_020ba784, /* SyncSessionCommFlags */
    func_ov037_020ba810, /* FinishCommSession */
    func_ov037_020ba894, /* NotifyCommSlotIfReady */
    func_ov037_020ba8c8, /* ResetCommSlotWhenIdle */
    func_ov037_020ba904, /* StoreCommResultSlot */
    func_ov037_020ba92c,
    func_ov037_020ba93c, /* AdvanceCommWhenReady */
    func_ov037_020ba964, /* MarkCommBusyWhenReady */
    func_ov037_020ba9a0, /* CloseCommAndRestoreRoom */
    func_ov037_020baa5c,
};
