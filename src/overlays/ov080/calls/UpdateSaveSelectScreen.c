#include "nitro/types.h"

typedef struct {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    u32 startTickLow;
    u32 startTickHigh;
    TweenFlags flags;
} Tween;

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0xcc];
    u8 saveData[0x3760];
} SaveSlot;

typedef struct {
    u32 words[0x3760 / 4];
} SaveData;

typedef struct {
    u8 slotIndex;
    u8 pad_01;
    u8 needsRedraw;
    u8 cursorShown;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 pad_08[2];
    u8 errorState;
    u8 pad_0B[5];
    BOOL cardRequestPending;
    u8 pad_14[4];
    BOOL busyHeld;
    u8 pad_1C[0x18];
    Tween fade;
    u8 pad_50[4];
    void *panel;
    u8 pad_58[0x14];
    void *cursorElement;
    u8 pad_70[8];
    SaveSlot slots[2];
    SaveData backup;
    u8 pad_A838[0xe8];
    BOOL unlockFlagA;
    BOOL unlockFlagB;
} SaveSelectScreen;

extern SaveData *data_0205fe0c;

extern int InvokeCallback(int slotIndex);
extern int PollCardThreadState(void);
extern int WriteCardSlotHeaders(int slotIndex);
extern void DecrementBusyCounterIfPositive(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void *FindWidgetById(void *panel, int elementId);
extern void SetEntrySlotsVisible(void *panel, void *element, BOOL visible);
extern void BuildSlotSummary(SaveSelectScreen *screen, SaveSlot *slot);
extern void HandleSlotReadResult(SaveSlot *slot, int mode);
extern void CountValidSlots(SaveSelectScreen *screen);
extern void func_ov080_020c55a4(SaveSelectScreen *screen, int value);
extern void func_ov073_020c1ed4(void *saveData, void *options);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern void SetPrimaryElementEnabled(BOOL enabled);
extern void RuntimeState_SetCondition(int value);
extern void func_ov039_020bc038(int value);
extern u32 func_ov039_020bc0f4(void);
extern int GetFieldCa4a(void);
extern void RuntimeState_SetFlags(int value);
extern void StartSubScene(int mode, int arg, int enable);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern void func_02052528(Tween *tween, int mode, int from, int to, int duration);
extern void func_02052570(Tween *tween);
extern void SetBrightnessAndSyncMain(s32 brightness);
extern void SetSecondaryBrightness(s32 brightness);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void SetGlobalPackedBit(int bit);
extern void ClearGlobalPackedBit(int bit);
extern void RebuildRecordCounters(void);
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern void ComputePlayerStats(void *saveData, void *record, int rebuild, int flags);
extern void FillSelectionRecordFromGroup(void);
extern void BuildSelectionEntryList(void);
extern void SyncSelectionRecordFromSlotEntry(void);
extern void func_0204fbb4(void);
extern void LoadSelectionPackedValues(void);

void UpdateSaveSelectScreen(SaveSelectScreen *screen)
{
    s32 brightness;
    u16 backdropColor;
    int value;
    BOOL idle;

    if (screen->errorState == 0) {
        switch (screen->step) {
        case 3:
            if (screen->cardRequestPending) {
                screen->cardRequestPending = FALSE;
                if (InvokeCallback(screen->slotIndex) != 0) {
                    break;
                }
                goto fail;
            }
            switch (PollCardThreadState()) {
            case 0:
                PlaySoundEffect(0, 0xb);
                screen->step = 4;
                SetEntrySlotsVisible(screen->panel, FindWidgetById(screen->panel, 8), FALSE);
                screen->needsRedraw = 1;
                BuildSlotSummary(screen, &screen->slots[screen->slotIndex]);
                CountValidSlots(screen);
                SetSecondaryElementEnabled(TRUE);
                screen->busyHeld = TRUE;
                screen->backup = *data_0205fe0c;
                break;
            case 1:
                break;
            default:
                goto fail;
            }
            break;
        fail:
            screen->errorState = 2;
            screen->needsRedraw = 1;
            DecrementBusyCounterIfPositive();
            break;
        case 5:
            if (screen->cardRequestPending) {
                screen->cardRequestPending = FALSE;
                if (WriteCardSlotHeaders(screen->slotIndex) == 0) {
                    screen->errorState = 2;
                }
                if (screen->errorState == 2) {
                    screen->needsRedraw = 1;
                    DecrementBusyCounterIfPositive();
                }
            }
            SampleTweenValue(&screen->fade, NULL);
            if (screen->fade.flags.finished) {
                PlaySoundEffect(0, 0xb);
                screen->step = 6;
                SetEntrySlotsVisible(screen->panel, FindWidgetById(screen->panel, 8), FALSE);
                screen->needsRedraw = 1;
                HandleSlotReadResult(&screen->slots[screen->slotIndex], 2);
                func_ov073_020c1ed4(NULL, NULL);
                CountValidSlots(screen);
                SetSecondaryElementEnabled(TRUE);
                screen->busyHeld = TRUE;
                if (screen->slots[0].status < 3 && screen->slots[1].status < 3) {
                    screen->unlockFlagA = FALSE;
                    screen->unlockFlagB = FALSE;
                }
            }
            break;
        case 7:
            SampleTweenValue(&screen->fade, &brightness);
            SetBrightnessAndSyncMain(brightness);
            SetSecondaryBrightness(brightness);
            if (screen->fade.flags.finished) {
                func_02052528(&screen->fade, 0, 0, 0x10, 0x10a);
                func_02052570(&screen->fade);
                screen->step = 8;
            }
            break;
        case 8:
            SampleTweenValue(&screen->fade, NULL);
            if (screen->fade.flags.finished) {
                backdropColor = 0x7fff;
                *(vu32 *)0x04000000 &= ~0x1f00;
                *(vu32 *)0x04001000 &= ~0x1f00;
                GX_LoadBGPltt(&backdropColor, 0, 2);
                GXS_LoadBGPltt(&backdropColor, 0, 2);
                StartSubScene(-1, 0x42b, 1);
                RuntimeState_SetFlags(1);
                screen->step++;
                MIi_CpuCopyFast(screen->slots[screen->slotIndex].saveData, data_0205fe0c, sizeof(SaveData));
                SetGlobalPackedBit(0x1a05);
                if (screen->unlockFlagA) {
                    SetGlobalPackedBit(0x1150);
                } else {
                    ClearGlobalPackedBit(0x1150);
                }
                if (screen->unlockFlagB) {
                    SetGlobalPackedBit(0x1151);
                } else {
                    ClearGlobalPackedBit(0x1151);
                }
                RebuildRecordCounters();
                ComputePlayerStats(data_0205fe0c, GetOverlaySelectionRecord(0), 1, 0);
                FillSelectionRecordFromGroup();
                BuildSelectionEntryList();
                SyncSelectionRecordFromSlotEntry();
                func_0204fbb4();
                LoadSelectionPackedValues();
                *(u16 *)((u8 *)data_0205fe0c + 0x2d36) = 0xffff;
                return;
            }
            break;
        case 4:
        case 6:
            if (screen->busyHeld) {
                screen->busyHeld = FALSE;
                DecrementBusyCounterIfPositive();
            }
            break;
        }
    }

    if (screen->errorState > 0x80) {
        SetEntrySlotsVisible(screen->panel, FindWidgetById(screen->panel, 8), FALSE);
    }

    idle = func_ov039_020bc0f4() == 0;
    if (idle) {
        value = 0;
        if (!screen->cursorShown) {
            SetEntrySlotsVisible(screen->panel, screen->cursorElement, FALSE);
            screen->cursorShown = TRUE;
        }
    } else {
        value = GetFieldCa4a();
        if (screen->cursorShown) {
            if (screen->step < 3) {
                SetEntrySlotsVisible(screen->panel, screen->cursorElement, TRUE);
            }
            screen->cursorShown = FALSE;
        }
    }
    func_ov080_020c55a4(screen, value);

    if (screen->errorState != 0) {
        screen->errorState |= 0x80;
        func_ov039_020bc038(0);
        SetPrimaryElementEnabled(FALSE);
        SetSecondaryElementEnabled(FALSE);
        RuntimeState_SetCondition(0);
        SetEntrySlotsVisible(screen->panel, screen->cursorElement, FALSE);
    }
}
