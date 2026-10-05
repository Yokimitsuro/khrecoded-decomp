#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    s32 taskHandle;
    void *resourceA;
    void *resourceB;
    void *resourceC;
    void *buffer;
    u8 pad_28[0xc];
    s32 unk_34;
} SceneState;

typedef struct {
    void *context;
    SceneState *scene;
} Ov032Globals;

typedef struct {
    u8 pad_0000[0x27fd];
    u8 flag0 : 1;
} SessionState;

extern Ov032Globals data_ov032_020c0080;
extern SessionState *data_ov001_020a0480;
extern void SetSoundListenersEnabled(int enabled);
extern void FreePointerIfSet(void **ptr);
extern void *PXI_Init_0202a64c();
extern void SuspendTaskAndSetFlag(void);
extern void func_ov001_0206a714(void);
extern int func_ov001_0206c6f4(void);
extern void func_ov001_02063c54(void);
extern void func_ov001_020646b8(s32 index);

void DestroySceneState(void) {
    SetSoundListenersEnabled(0);
    FreePointerIfSet(&data_ov032_020c0080.scene->buffer);
    PXI_Init_0202a64c(data_ov032_020c0080.scene->resourceA);
    PXI_Init_0202a64c(data_ov032_020c0080.scene->resourceB);
    if (data_ov032_020c0080.scene->resourceC != (void *)-1) {
        PXI_Init_0202a64c(data_ov032_020c0080.scene->resourceC);
    }
    SuspendTaskAndSetFlag();
    if (data_ov032_020c0080.scene->taskHandle != -1) {
        func_ov001_0206a714();
        data_ov032_020c0080.scene->taskHandle = -1;
    }
    func_ov001_0206c6f4();
    func_ov001_02063c54();
    if (data_ov032_020c0080.scene->unk_34 != 0) {
        func_ov001_020646b8(10);
        data_ov001_020a0480->flag0 = 0;
    } else {
        data_ov001_020a0480->flag0 = 1;
    }
    data_ov032_020c0080.scene = NULL;
}
