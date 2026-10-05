#include "nitro/types.h"

typedef void *SceneHandler;

typedef struct {
    SceneHandler states[9];
    u8 pad_24[4];
    SceneHandler onEnter;
} SceneHandlerTable;

extern void func_ov029_020ba9d0(int arg0);
extern BOOL func_ov029_020ba9f4(void);
extern u32 func_ov029_020baa20(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern u32 func_ov029_020baa44(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern BOOL HasOv029ObjectField28(void);
extern void ReleaseOv029Object(void);
extern void func_ov029_020baaa4(void *params);
extern u32 func_ov029_020baaec(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern void func_ov029_020ba88c(int mode);
extern u32 func_ov029_020baaf4(u32 argument0, u32 argument1, u32 argument2, u32 argument3);

void InstallOv029SceneHandlers(SceneHandlerTable *table) {
    table->states[0] = func_ov029_020ba9d0;
    table->states[1] = func_ov029_020ba9f4;
    table->states[2] = func_ov029_020baa20;
    table->states[3] = func_ov029_020baa44;
    table->states[4] = HasOv029ObjectField28;
    table->states[5] = ReleaseOv029Object;
    table->states[6] = func_ov029_020baaa4;
    table->states[7] = func_ov029_020baaec;
    table->states[8] = func_ov029_020ba88c;
    table->onEnter = func_ov029_020baaf4;
}
