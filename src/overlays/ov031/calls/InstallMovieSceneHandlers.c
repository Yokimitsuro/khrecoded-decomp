#include "nitro/types.h"

typedef int (*SceneHandler)(void);

typedef struct {
    SceneHandler states[9];
    u8 pad_24[4];
    SceneHandler onEnter;
    SceneHandler onExit;
} SceneHandlerTable;

extern int func_ov031_020bb494(void);
extern int func_ov031_020bb4ac(void);
extern int func_ov031_020bb4c8(void);
extern int SetModeByte(void);
extern int IsPxiFifoTagSet(void);
extern int ReleasePxiFifoTag(void);
extern int ApplyStartParams(void);
extern int IsStopFlagClear(void);
extern int ApplyOverlayScaleMode_020bab40(void);
extern int func_ov031_020bbf44(void);
extern int ResetSceneState(void);
extern void ApplyAreaMusicEntry(int index);

void InstallMovieSceneHandlers(SceneHandlerTable *table)
{
    table->states[0] = func_ov031_020bb494;
    table->states[1] = func_ov031_020bb4ac;
    table->states[2] = func_ov031_020bb4c8;
    table->states[3] = SetModeByte;
    table->states[4] = IsPxiFifoTagSet;
    table->states[5] = ReleasePxiFifoTag;
    table->states[6] = ApplyStartParams;
    table->states[7] = IsStopFlagClear;
    table->states[8] = ApplyOverlayScaleMode_020bab40;
    table->onEnter = func_ov031_020bbf44;
    table->onExit = ResetSceneState;
    ApplyAreaMusicEntry(2);
}
