#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_0000[0xf078];
    int frameCounter;
    int blinkPhase;
    int waveAngle;
} MenuScene;

extern void (*const gStoryReportStateHandlers[])(void);
extern s16 data_02053580[];
extern int func_ov097_020c1590(MenuScene *scene);
extern void func_ov097_020bfb58(int mode, MenuScene *scene);
extern void UpdateScrollBarDrag_020c0f18(MenuScene *scene);
extern void func_ov097_020bff94(MenuScene *scene);
extern void DrawScrolledPopups(MenuScene *scene);
extern int GetScrollTrackRow(int trackIndex);
extern void SetScrollTrackTarget(int trackIndex, int row);
extern void EaseScrollTrack(int trackIndex);

void UpdateMenuScene(MenuScene *scene)
{
    void (*handler)(void) = gStoryReportStateHandlers[func_ov097_020c1590(scene)];
    fx32 wave;

    if (handler != NULL) {
        handler();
    }
    if (++scene->frameCounter >= 60) {
        scene->frameCounter = 0;
        scene->blinkPhase = (scene->blinkPhase + 1) % 2;
        func_ov097_020bfb58(0, scene);
    }
    UpdateScrollBarDrag_020c0f18(scene);
    func_ov097_020bff94(scene);
    DrawScrolledPopups(scene);
    *(vu32 *)0x04001010 = (GetScrollTrackRow(0) << 16) & 0x01ff0000;
    scene->waveAngle += 0xb4;
    if (scene->waveAngle >= 0x8000) {
        scene->waveAngle -= 0x8000;
    }
    wave = (fx32)(((s64)data_02053580[scene->waveAngle >> 4] * 0x8000 + 0x800) >> 12);
    SetScrollTrackTarget(0, wave >> 12);
    EaseScrollTrack(0);
}
