#include "nitro/types.h"

typedef void *SceneHandler;

typedef struct {
    SceneHandler states[9];
    u8 pad_24[4];
    SceneHandler onEnter;
    SceneHandler onExit;
} SceneHandlerTable;

extern void func_ov028_020bafe8(int arg0);
extern BOOL func_ov028_020bb00c(void);
extern u32 func_ov028_020bb038(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern void SetFieldModeFlag(u8 mode);
extern BOOL func_ov028_020bb080(void);
extern void ReleaseHandle_020bb0a4(void);
extern void func_ov028_020bb0c4(void *params);
extern BOOL IsSceneUnpaused(void);
extern void func_ov028_020bae88(s32 mode);
extern u32 func_ov028_020bb19c(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern void func_ov028_020bb1b4(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void ApplyAreaMusicEntry(int mode);

void InstallSceneHandlers(SceneHandlerTable *table) {
    table->states[0] = func_ov028_020bafe8;
    table->states[1] = func_ov028_020bb00c;
    table->states[2] = func_ov028_020bb038;
    table->states[3] = SetFieldModeFlag;
    table->states[4] = func_ov028_020bb080;
    table->states[5] = ReleaseHandle_020bb0a4;
    table->states[6] = func_ov028_020bb0c4;
    table->states[7] = IsSceneUnpaused;
    table->states[8] = func_ov028_020bae88;
    table->onEnter = func_ov028_020bb19c;
    table->onExit = func_ov028_020bb1b4;
    ApplyAreaMusicEntry(func_ov001_020645c8(0x3ee4) ? 4 : 0);
}
