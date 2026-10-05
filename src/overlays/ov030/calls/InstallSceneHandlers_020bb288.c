#include "nitro/types.h"

typedef int (*SceneHandler)(void);

typedef struct {
    SceneHandler states[9];
    u8 pad_24[4];
    SceneHandler onEnter;
    SceneHandler onExit;
} SceneHandlerTable;

extern int func_ov030_020babc8(void);
extern int func_ov030_020babe0(void);
extern int func_ov030_020babfc(void);
extern int func_ov030_020bac14(void);
extern int MobiClip_IsDecoderReady(void);
extern int MobiClip_CloseDecoder(void);
extern int func_ov030_020bac68(void);
extern int IsSceneUnpaused_020bacd4(void);
extern int ApplyOverlayScaleMode(void);
extern int func_ov030_020bb230(void);
extern int SuspendSceneAtQuarterRate(void);
extern void ApplyAreaMusicEntry(int mode);

void InstallSceneHandlers_020bb288(SceneHandlerTable *table) {
    table->states[0] = func_ov030_020babc8;
    table->states[1] = func_ov030_020babe0;
    table->states[2] = func_ov030_020babfc;
    table->states[3] = func_ov030_020bac14;
    table->states[4] = MobiClip_IsDecoderReady;
    table->states[5] = MobiClip_CloseDecoder;
    table->states[6] = func_ov030_020bac68;
    table->states[7] = IsSceneUnpaused_020bacd4;
    table->states[8] = ApplyOverlayScaleMode;
    table->onEnter = func_ov030_020bb230;
    table->onExit = SuspendSceneAtQuarterRate;
    ApplyAreaMusicEntry(1);
}
