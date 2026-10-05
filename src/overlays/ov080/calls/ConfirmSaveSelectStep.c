#include "nitro/types.h"

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0x382c];
} SaveSlot;

typedef struct {
    u8 pad_00[0x28c4];
    u32 saveStamp;
} SaveFields;

typedef struct {
    u8 bytes[0x20];
} FadeRecord;

typedef struct {
    u8 slotIndex;
    u8 pad_01;
    u8 needsRedraw;
    u8 pad_03;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 promptOpen;
    u8 pad_09[2];
    u8 overwriting;
    u8 pad_0C[4];
    int saving;
    int returnMode;
    int busy;
    int unk_1C;
    u32 latestStamp;
    u8 pad_24[0x10];
    FadeRecord fade;
    void *panel;
    u8 pad_58[0x20];
    SaveSlot slots[2];
} SaveSelectScreen;

extern SaveFields *data_0205fe0c;
extern int func_ov039_020bc934(void);
extern void StartSubScene(int a, int b, int c);
extern void DecrementBusyCounterIfPositive(void);
extern void IncrementBusyCounter(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern u32 func_0202a9e4(u32 range);
extern void SetGlobalPackedBit(int bitIndex);
extern void func_02052528(FadeRecord *record, int value0, int value1, int value2, int value3);
extern void func_02052570(FadeRecord *record);
extern void *FindWidgetById(void *root, int id);
extern void func_ov027_020b95a0(void *panel, void *element, BOOL visible);
extern void SetPrimaryElementEnabled(BOOL enabled);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern BOOL PrepareAndStartStream(int streamIndex, int streamId);
extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);

void ConfirmSaveSelectStep(SaveSelectScreen *screen)
{
    switch (screen->step) {
    case 0:
        if (func_ov039_020bc934() != 3) {
            screen->step = 1;
            screen->promptOpen = 1;
            PlaySoundEffect(0, 1);
        } else {
            switch (screen->slots[screen->slotIndex].status) {
            case 0:
                PlaySoundEffect(0, 4);
                break;
            case 1:
                screen->step = 1;
                screen->overwriting = 1;
                screen->promptOpen = 1;
                PlaySoundEffect(0, 1);
                break;
            default:
                screen->step = 1;
                screen->promptOpen = 1;
                PlaySoundEffect(0, 1);
                break;
            }
        }
        break;
    case 1:
        if (screen->promptOpen == 0) {
            if (screen->overwriting != 0) {
                screen->step = 5;
                screen->saving = 1;
                func_02052528(&screen->fade, 0, 0, 0x1000, 2000);
                func_02052570(&screen->fade);
            } else if (func_ov039_020bc934() != 3) {
                screen->step = 3;
                screen->latestStamp = (screen->latestStamp & 0xf0000000) | ((screen->latestStamp + 1) & 0x0fffffff);
                data_0205fe0c->saveStamp = ((screen->slotIndex << 28) & 0x30000000) | (screen->latestStamp & 0x0fffffff) | ((func_0202a9e4(4) << 30) & 0xc0000000);
                screen->saving = 1;
                if (screen->returnMode != 0) {
                    SetGlobalPackedBit(0xbea);
                }
            } else {
                screen->step = 7;
                func_02052528(&screen->fade, 0, 0, 0x10, 0x42a);
                func_02052570(&screen->fade);
            }
            if (screen->step != 7) {
                SetSecondaryElementEnabled(FALSE);
                func_ov027_020b95a0(screen->panel, FindWidgetById(screen->panel, 8), TRUE);
                PlaySoundEffect(0, 1);
                IncrementBusyCounter();
            } else {
                SetPrimaryElementEnabled(FALSE);
                SetSecondaryElementEnabled(FALSE);
                PrepareAndStartStream(1, 3);
                StopSoundStreamAtIndex(0, 0x1e);
            }
        } else {
            screen->step = 0;
            screen->overwriting = 0;
            PlaySoundEffect(0, 1);
        }
        break;
    case 2:
        if (screen->promptOpen == 0) {
            StartSubScene(-1, -1, 1);
        } else {
            screen->step = 0;
            screen->overwriting = 0;
        }
        PlaySoundEffect(0, 1);
        break;
    case 4:
    case 6:
        if (screen->busy != 0) {
            screen->busy = 0;
            DecrementBusyCounterIfPositive();
        }
        if (screen->returnMode != 0) {
            StartSubScene(-1, -1, 1);
        } else {
            screen->step = 0;
            screen->overwriting = 0;
        }
        PlaySoundEffect(0, 1);
        break;
    }
    screen->needsRedraw = 1;
}
