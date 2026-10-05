#include "nitro/types.h"

typedef struct SceneMessage {
    s32 state;
    u8 pad_04[0x24];
    s64 closeTick;
    u8 pad_30[0x38];
    u16 *textBuffer;
    u16 *textCursor;
    u8 pad_70[0x8];
    s32 refreshOnClose;
} SceneMessage;

typedef struct SceneGlobals {
    u32 unk_00;
    void *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04c4;
extern s64 OS_GetTick(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern u32 func_ov001_0207b3f4(void);
extern void LoadFieldBottomRowTiles(void *scene);

void CloseSceneMessage(SceneMessage *message)
{
    message->closeTick = OS_GetTick();
    message->state = 3;
    NNSi_FndFreeFromDefaultHeap(message->textBuffer);
    message->textBuffer = NULL;
    message->textCursor = NULL;
    if (message->refreshOnClose != 0 && func_ov001_0207b3f4() == 0) {
        LoadFieldBottomRowTiles(data_ov001_020a04c4.scene);
    }
}
