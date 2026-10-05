#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0xb70];
    PanelStackEntry stack[6];
    int depth;
} PanelScene;

extern void *func_ov039_020bc1dc(void);
extern void *func_ov027_020b9114(void *container);
extern void EnterPanelState_020c6138(PanelScene *scene, int newState, int oldState);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void PushPanelState(PanelScene *scene, int stateId)
{
    int previousState = scene->stack[scene->depth].stateId;

    scene->depth++;
    scene->stack[scene->depth].stateId = stateId;
    scene->stack[scene->depth].focusElement = func_ov027_020b9114(func_ov039_020bc1dc());
    EnterPanelState_020c6138(scene, stateId, previousState);
    if (stateId != 0x10 && stateId != 0x11) {
        PlaySoundEffect(0, 1);
    }
}
