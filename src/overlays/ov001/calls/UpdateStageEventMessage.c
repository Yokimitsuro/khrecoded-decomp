#include "nitro/types.h"

typedef struct EventInfo {
    u16 messageId;
    u16 isMessage : 1;
    u16 isTicker : 1;
    u16 reserved : 14;
    u8 pad_04[0x18];
    u32 tickerMode;
    u32 tickerValue;
} EventInfo;

typedef struct PendingRequest {
    s32 unk_00;
    s32 handle;
    s32 active;
} PendingRequest;

typedef struct Manager {
    u8 pad_00[0x3c];
    PendingRequest request;
} Manager;

extern Manager *data_ov001_020a04a4;

extern int IsStageEventReady(u16 id);
extern u32 GetBoundedEntryField(int index);
extern BOOL func_ov001_02087988(u16 id, EventInfo *info);
extern s32 func_ov001_02063a38(void);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern void ShowFieldMessageLine(u16 tickerMode, u32 tickerValue, int messageId, BOOL resetTicker);
extern void HideFieldMessageLine(void);
extern void ResetPendingRequest(void);
extern void StageRecord_SetFlagBit2(u16 id);
extern void *func_ov001_02071690(u16 id);

void UpdateStageEventMessage(int id)
{
    PendingRequest *request = &data_ov001_020a04a4->request;
    EventInfo info;
    BOOL reset;

    switch (request->active) {
    case 0:
        if (id != -1 && IsStageEventReady(id)) {
            reset = FALSE;
            GetBoundedEntryField(0);
            if (func_ov001_02087988(id, &info)) {
                if ((!info.isTicker || info.isMessage) && func_ov001_02063a38() != 6) {
                    if (IsPlayerEntryFlagSet(0, 9)) {
                        reset = TRUE;
                    }
                    ShowFieldMessageLine(info.tickerMode, (u16)info.tickerValue, info.messageId, reset);
                } else {
                    HideFieldMessageLine();
                }
                request->handle = id;
                request->active = 1;
            }
        }
        break;
    case 1:
        if (id == -1) {
            id = request->handle;
        }
        if (!IsStageEventReady(id)) {
            ResetPendingRequest();
            return;
        }
        StageRecord_SetFlagBit2(id);
        if (id != request->handle) {
            request->active = 0;
            UpdateStageEventMessage(id);
            return;
        }
        if (func_ov001_02087988(id, &info)) {
            func_ov001_02071690(info.tickerMode);
        }
        break;
    }
}
