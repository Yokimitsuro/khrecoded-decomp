#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    int kind;
    u8 pad[0x104];
} PanelModelSlot;

typedef struct {
    u8 pad0[4];
    int selectedSlot;
    u8 pad1[0x118 - 0x8];
    PanelModelSlot slots[10];
    u8 pad2[0xb70 - 0x118 - 10 * 0x108];
    PanelStackEntry stack[6];
    int depth;
    u8 pad3[0xbc0 - 0xba4];
    int confirmFlag;
    int cancelFlag;
    int currentKind;
    int requiredKind;
} PanelScene;

typedef struct {
    u8 pad[0xc];
    int mode;
} FocusElement;

extern void *func_ov039_020bc1dc(void);
extern FocusElement *func_ov027_020b9114(void *container);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void PushPanelState(PanelScene *scene, int stateId);

void ConfirmPanelSelection(PanelScene *scene)
{
    int kind = scene->slots[scene->selectedSlot].kind;

    switch (scene->stack[scene->depth].stateId) {
    case 1:
        if (kind == 7) {
            scene->confirmFlag = TRUE;
            if (IsGlobalPackedBitSet(0x4436) && scene->requiredKind == kind) {
                PushPanelState(scene, 4);
                return;
            }
            PushPanelState(scene, 5);
            scene->cancelFlag = TRUE;
        } else if (kind == scene->currentKind) {
            scene->confirmFlag = FALSE;
            PushPanelState(scene, 0xf);
        } else {
            scene->confirmFlag = TRUE;
            if (IsGlobalPackedBitSet(0x4436) && scene->requiredKind == kind) {
                PushPanelState(scene, 4);
                return;
            }
            PushPanelState(scene, 5);
            scene->cancelFlag = TRUE;
        }
        break;
    case 2:
        if (kind == scene->currentKind && func_ov027_020b9114(func_ov039_020bc1dc())->mode == 2) {
            scene->confirmFlag = FALSE;
            PushPanelState(scene, 0xa);
            return;
        }
        scene->confirmFlag = TRUE;
        if (kind == scene->requiredKind) {
            scene->cancelFlag = TRUE;
            PushPanelState(scene, 6);
        } else {
            PushPanelState(scene, 5);
            scene->cancelFlag = TRUE;
        }
        break;
    case 3:
        if ((kind == 7 && func_ov027_020b9114(func_ov039_020bc1dc())->mode == 2) ||
            (kind != 7 && kind == scene->currentKind)) {
            scene->confirmFlag = FALSE;
            PushPanelState(scene, 0xe);
            return;
        }
        scene->confirmFlag = TRUE;
        if (IsGlobalPackedBitSet(0x4436)) {
            if (scene->requiredKind == kind) {
                scene->cancelFlag = FALSE;
                PushPanelState(scene, 4);
            } else {
                scene->cancelFlag = TRUE;
                PushPanelState(scene, 5);
            }
        } else {
            scene->cancelFlag = TRUE;
            PushPanelState(scene, 6);
        }
        break;
    }
}
