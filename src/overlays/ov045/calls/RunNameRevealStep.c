#include "nitro/types.h"

typedef struct Tween {
    u8 unknown_00[0x18];
    u32 unknownFlags : 2;
    u32 finished : 1;
} Tween;

typedef struct NamedEntry {
    u8 unknown_00[0x40];
    const u16 *name;
} NamedEntry;

typedef struct RevealWork {
    u8 unknown_00[0x04];
    int entryIndex;
    u8 unknown_08[0x08];
    s16 step;
    u8 unknown_12[0x06];
    BOOL started;
    u8 unknown_1c[0x18];
    BOOL screensDirty;
    u8 records[0x4c];
    u16 subScreen[0x600];
    u16 mainScreen[0x600];
    u8 textLayer[0x34];
    u8 sprite[0x178];
    Tween tween;
} RevealWork;

extern RevealWork *data_ov045_020c08a0;
extern u16 data_02060500;

extern void G3X_SetClearColor(unsigned color, unsigned alpha, unsigned depth, unsigned polygonId, BOOL fog);
extern void InvokeCallbackForRecordId(void *pool, u32 recordId);
extern void StartUnitTween(Tween *tween, int duration);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern NamedEntry *GetRecordSlotPair0Entry(s32 index);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer(void *layer);
extern void ArmTagById(void *pool, int id);
extern void DisarmTagById(void *pool, int id);
extern void func_02052528(Tween *tween, int mode, int startValue, int endValue, int duration);
extern void func_02052570(Tween *tween);
extern void SetBrightnessAndSyncMain(int brightness);
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9d38(void *table, int row);
extern void func_ov027_020b7df4(void *pool);
extern void func_ov045_020c0354(int left, int right, int top, int bottom);
extern void DrawRotatedSprite(void *sprite, int size, int angle);
extern int NNS_GfdRegisterNewVramTransferTask(int engine, int offset, void *src, int size);

#define REG_DISPCNT (*(vu32 *)0x04000000)

int RunNameRevealStep(void)
{
    RevealWork *work = data_ov045_020c08a0;
    int size = 0x1000;
    int angle = 0;
    s32 introValue;
    s32 spinValue;
    s32 shrinkValue;
    s32 fadeValue;

    if (work->step < 0) {
        return 0;
    }
    G3X_SetClearColor(0, 0, 0x7fff, 0x3f, FALSE);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0xd00;
    switch (work->step) {
    case 0:
        if (!work->started) {
            InvokeCallbackForRecordId(work->records, 0);
            StartUnitTween(&work->tween, 500);
            work->started = TRUE;
        }
        SampleTweenValue(&work->tween, &introValue);
        size = 0;
        if (work->tween.finished) {
            work->started = FALSE;
            work->step++;
        }
        break;
    case 1:
        if (!work->started) {
            StartUnitTween(&work->tween, 300);
            work->started = TRUE;
        }
        SampleTweenValue(&work->tween, &spinValue);
        size = spinValue;
        angle = spinValue << 4;
        if (work->tween.finished) {
            work->started = FALSE;
            work->step++;
        }
        break;
    case 2:
        if (!work->started) {
            StartUnitTween(&work->tween, 300);
            work->started = TRUE;
            PlaySoundEffect(0, 9);
        }
        SampleTweenValue(&work->tween, &shrinkValue);
        if (work->tween.finished) {
            work->started = FALSE;
            work->step++;
        }
        break;
    case 3:
        if (!work->started) {
            const u16 *name = GetRecordSlotPair0Entry(work->entryIndex)->name;
            FillBackgroundLayerRect(work->textLayer, work->mainScreen, 10, 2, 0xf);
            DrawTextAnchored(work->textLayer, 0x30, 1, 2, 0x10, name);
            Text_UploadTileBuffer(work->textLayer);
            ArmTagById(work->records, 0);
            work->started = TRUE;
        } else if (data_02060500 & 0x2f0f) {
            PlaySoundEffect(0, 1);
            work->started = FALSE;
            work->step++;
            DisarmTagById(work->records, 0);
            InvokeCallbackForRecordId(work->records, 2);
        }
        break;
    case 4:
        if (!work->started) {
            func_02052528(&work->tween, 0, 0, -0x10000, 1000);
            func_02052570(&work->tween);
            work->started = TRUE;
        }
        SampleTweenValue(&work->tween, &fadeValue);
        fadeValue /= 4096;
        SetBrightnessAndSyncMain(fadeValue);
        if (work->tween.finished) {
            work->started = FALSE;
            work->step = -1;
            func_ov027_020b9d38(func_ov001_0207123c(), 0xb);
            func_ov027_020b9d38(func_ov001_0207123c(), 0xa);
        }
        break;
    }
    func_ov027_020b7df4(work->records);
    func_ov045_020c0354(0, 0x100000, 0, 0xc0000);
    DrawRotatedSprite(work->sprite, size, angle);
    if (work->screensDirty) {
        NNS_GfdRegisterNewVramTransferTask(0xb, 0, work->subScreen, 0x600);
        NNS_GfdRegisterNewVramTransferTask(0xa, 0, work->mainScreen, 0x600);
        work->screensDirty = FALSE;
    }
    return 0;
}
