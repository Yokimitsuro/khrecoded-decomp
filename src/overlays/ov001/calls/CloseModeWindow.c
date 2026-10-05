#include "nitro/types.h"

typedef struct WindowSound {
    u8 pad_00[0x10];
    int enabled;
} WindowSound;

typedef struct ModeWindow {
    int layer;
    int unk4;
    int state;
    u8 pad_0c[0x10];
    u8 fade[0x38];
    WindowSound sound;
} ModeWindow;

extern int *data_ov001_020a04e4;
extern int func_ov001_0207123c(void);
extern void *GetSceneTagTracker(void);
extern void *FindLoadedElementById(void *pool, int tag);
extern void SetTagRecordArmed(void *pool, void *record, int value);
extern void func_02052528(void *record, int value0, int value1, int value2, int value3);
extern void func_02052570(void *record);
extern void RefreshWindowHighlight(ModeWindow *window, int unused, int layer);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void FreeModeResources(ModeWindow *window);
extern void func_ov001_020795c4(ModeWindow *window);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *arg);

void CloseModeWindow(ModeWindow *window) {
    void *pool;
    WindowSound *sound;
    void *record;

    func_ov001_0207123c();
    pool = GetSceneTagTracker();
    sound = &window->sound;
    SetTagRecordArmed(pool, FindLoadedElementById(pool, 6), 0);
    SetTagRecordArmed(pool, FindLoadedElementById(pool, 13), 0);
    SetTagRecordArmed(pool, FindLoadedElementById(pool, 14), 0);
    func_02052528(window->fade, 0, 0x64000, 0, 100);
    func_02052570(window->fade);
    RefreshWindowHighlight(window, window->layer, 9);
    RefreshWindowHighlight(window, window->layer, 10);
    if (*data_ov001_020a04e4 == 1) {
        if (window->sound.enabled != 0) {
            PlaySoundEffect(0, 1);
        }
        FreeModeResources(window);
        window->state = 0;
        RefreshWindowHighlight(window, window->layer, 11);
        return;
    }
    func_ov001_020795c4(window);
    window->state = 7;
    switch (*data_ov001_020a04e4) {
    default:
        goto play;
    case 5:
    case 7:
    case 10:
        record = FindActiveRecordById(pool, 600);
        break;
    case 6:
        record = FindActiveRecordById(pool, 601);
        break;
    }
    func_ov027_020b8288(pool, record);
play:
    if (sound->enabled != 0) {
        PlaySoundEffect(0, 1);
        return;
    }
    PlaySoundEffect(0, 7);
}
