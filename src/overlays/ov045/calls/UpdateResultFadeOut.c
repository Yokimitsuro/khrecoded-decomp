#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad00[0x18];
    u32 unused0 : 2;
    u32 finished : 1;
} Tween;

typedef struct {
    u8 pad00[0x10];
    s16 phase;
    u8 pad12[6];
    BOOL started;
    u8 pad1c[0x18];
    void *pool;
    u8 pad38[0x19f8];
    Tween fade;
} ResultScreen;

extern ResultScreen *data_ov045_020c08a0;
extern u16 data_02060500;

extern void InvokeCallbackForRecordId(void *pool, u32 recordId);
extern void PlaySoundChecked(void *ptr, int arg);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_02052528(Tween *tween, int mode, fx32 startValue, fx32 endValue, int duration);
extern void func_02052570(Tween *tween);
extern void SampleTweenValue(Tween *tween_state, s32 *output_value);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9d38(void *table, int id);

int UpdateResultFadeOut(void)
{
    ResultScreen *screen = data_ov045_020c08a0;
    s32 brightness;

    if (screen->phase < 0) {
        return 0;
    }
    switch (screen->phase) {
    case 0:
        if (!screen->started) {
            InvokeCallbackForRecordId(screen->pool, 0x10f);
            PlaySoundChecked(NULL, 0x12);
            screen->started = TRUE;
            break;
        }
        if (!(data_02060500 & 0x2f0f)) {
            break;
        }
        PlaySoundEffect(0, 1);
        screen->started = FALSE;
        screen->phase++;
        /* Fall through to start the fade. */
    case 1:
        if (!screen->started) {
            screen->started = TRUE;
            func_02052528(&screen->fade, 0, 0, -0x10000, 1000);
            func_02052570(&screen->fade);
        }
        SampleTweenValue(&screen->fade, &brightness);
        brightness /= 0x1000;
        SetBrightnessAndSyncMain(brightness);
        SetSecondaryBrightness(brightness);
        if (screen->fade.finished) {
            screen->started = FALSE;
            screen->phase = -1;
            func_ov027_020b9d38(func_ov001_0207123c(), 0xb);
        }
        break;
    }
    return 0;
}

