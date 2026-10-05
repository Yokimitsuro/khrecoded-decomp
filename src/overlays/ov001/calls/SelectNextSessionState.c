#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 6;
    u32 resumePending : 1;
    u32 unk_7 : 5;
    u32 promptOpen : 1;
    u32 unk_13 : 19;
} SessionFlags;

typedef struct SessionStatus {
    u8 active : 1;
    u8 panelMode : 2;
    u8 unk_3 : 1;
    u8 bit4 : 1;
    u8 unk_5 : 1;
    u8 bit6 : 1;
    u8 unk_7 : 1;
} SessionStatus;

typedef struct PromptHandlers {
    u8 pad_00[0xc];
    void (*close)(int arg);
    int (*poll)(void);
} PromptHandlers;

typedef struct EntryStats {
    u16 unk_0;
    u16 count;
} EntryStats;

typedef struct EntryData {
    u8 pad_000[0x1d4];
    EntryStats *stats;
} EntryData;

typedef struct Session {
    u8 pad_0000[0x1b];
    u8 redrawRequested;
    u32 unk_1C;
    u32 displayFlags;
    u8 pad_0024[0x20e - 0x24];
    s16 unk_20E;
    u8 pad_0210[0x4];
    SessionFlags flags;
    u8 pad_0218[0x2738 - 0x218];
    s8 inputFlags;
    u8 pad_2739[0xb];
    s8 pendingCount;
    s8 pendingIndex;
    u8 pad_2746[0x70];
    SessionStatus status;
    u8 pad_27B7;
    u8 unk_27B8[0x45];
    SessionStatus resumeStatus;
    u8 pad_27FE[0xe];
    PromptHandlers handlers;
    u8 pad_2820[0x84];
    s8 closeArg;
} Session;

extern Session *data_ov001_020a0480;
extern int func_ov001_0206dc38(void);
extern EntryData *GetBoundedEntryField(int index);
extern void func_ov001_020645e8(u32 eventId);
extern BOOL func_ov001_020645c8(u32 eventId);
extern u32 GetClampedTimerValue(void);
extern u32 _u32_div_f(u32 dividend, u32 divisor);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void func_ov001_020690dc(void);
extern void func_ov001_02068e54(void);
extern void SaveElapsedSeconds(void);
extern int func_ov001_0206dc4c(int index);
extern u16 GetBiasAdjustedField(int index);
extern void func_ov001_020645f4(int values, u32 extra);
extern void func_ov001_0206a8c8(int value);
extern void NotifySceneActorsPaused(int enable);
extern int DispatchPartyEntryByMode(int index);
extern int IsSessionLinked(void);
extern int func_ov001_02062c64(void);
extern void func_ov001_0206e444(int enable);
extern void SetMenuHighlight(int enable);
extern int IsEntryFlag2Active(int index);
extern u32 func_ov001_0206685c(void);
extern void Camera_SaveSnapshot(void *buffer);
extern u8 func_ov001_0207b484(void);
extern void func_ov001_0208707c(int enable);
extern void func_ov001_02063130(int index, int param);

int SelectNextSessionState(void)
{
    Session *session = data_ov001_020a0480;
    PromptHandlers *handlers = &session->handlers;

    if (func_ov001_0206dc38() > 0 && GetBoundedEntryField(0)->stats->count > 1) {
        func_ov001_020645e8(0x35c9);
    }
    if (func_ov001_020645c8(0x35f0)) {
        WriteSessionPackedBits(0x35e6, 10, _u32_div_f(GetClampedTimerValue(), 1000));
    }
    if (session->flags.resumePending) {
        func_ov001_020690dc();
        func_ov001_02068e54();
        handlers->close(session->closeArg);
        if (session->unk_20E == -2) {
            SaveElapsedSeconds();
            func_ov001_020645f4(func_ov001_0206dc4c(0), GetBiasAdjustedField(0));
            func_ov001_0206a8c8(0x4000);
            session->resumeStatus.active = 1;
            NotifySceneActorsPaused(1);
            if (DispatchPartyEntryByMode(0)) {
                data_ov001_020a0480->status.bit6 = 1;
            }
        } else {
            NotifySceneActorsPaused(0);
        }
        session->flags.resumePending = FALSE;
        session->flags.promptOpen = FALSE;
        return 10;
    }
    if (IsSessionLinked() && func_ov001_02062c64()) {
        if (session->flags.promptOpen) {
            func_ov001_0206e444(0);
            SetMenuHighlight(0);
        }
        session->status.bit4 = 1;
        func_ov001_020690dc();
        func_ov001_02068e54();
        session->displayFlags |= 0x10;
        session->flags.promptOpen = FALSE;
        data_ov001_020a0480->redrawRequested = 1;
        return 7;
    }
    if (session->flags.promptOpen) {
        if (session->unk_20E != -2 || IsEntryFlag2Active(0)) {
            session->flags.promptOpen = FALSE;
        } else if (!func_ov001_0206685c()) {
            NotifySceneActorsPaused(1);
            func_ov001_020690dc();
            func_ov001_0206e444(1);
            Camera_SaveSnapshot(session->unk_27B8);
            session->status.panelMode = func_ov001_0207b484();
            session->flags.resumePending = TRUE;
            session->pendingCount = 0;
            session->pendingIndex = 0;
            func_ov001_0208707c(1);
        }
        return -1;
    }
    if (session->inputFlags & 0x80) {
        func_ov001_020690dc();
        func_ov001_02068e54();
        data_ov001_020a0480->redrawRequested = 1;
        return 8;
    }
    if (handlers->poll != NULL && handlers->poll()) {
        func_ov001_020690dc();
        func_ov001_02068e54();
        handlers->close(0);
        return 10;
    }
    if (session->pendingCount > 0) {
        func_ov001_02063130(session->pendingIndex, 0);
        func_ov001_020690dc();
        func_ov001_02068e54();
        handlers->close(0);
        session->flags.promptOpen = FALSE;
        return 10;
    }
    return -1;
}
