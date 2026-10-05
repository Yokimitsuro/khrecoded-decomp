#include "nitro/types.h"

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    void **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern void PopVramState(void);
extern void *ActorSlot_GetByIndex(u16 slotIndex);
extern u16 ActorSlot_GetFlagsByIndex(u16 slotIndex);
extern void func_ov001_02089f44(void *actor);

int ScriptCmd_ReleaseSceneActors(ScriptContext *context)
{
    int index;

    PopVramState();
    if (context->scene->actorObjects != NULL) {
        for (index = 0; index < 0x200; index++) {
            if (ActorSlot_GetByIndex(index) == NULL || (ActorSlot_GetFlagsByIndex(index) & 4) == 0) {
                if (context->scene->actorObjects[index] != NULL) {
                    func_ov001_02089f44(context->scene->actorObjects[index]);
                }
            }
        }
    }
    return 1;
}
