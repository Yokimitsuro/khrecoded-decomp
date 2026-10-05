#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[8];
    u8 pad_958[0x218];
    PanelStackEntry stack[6];
    int depth;
    u8 pad_ba4[0x1c];
    int pendingState;
    int pendingTimer;
    u32 lockedId;
    u32 exclusiveId;
} PanelScene;

extern void PushPanelState(PanelScene *scene, int stateId);

void ConfirmSelectedEntry(PanelScene *scene)
{
    u32 id = scene->entries[scene->cursor].id;

    switch (scene->stack[scene->depth].stateId) {
    case 1:
        if (id == scene->lockedId) {
            scene->pendingState = 0;
            PushPanelState(scene, 0xf);
            return;
        }
        scene->pendingState = 2;
        PushPanelState(scene, 0xd);
        return;
    case 2:
        if (id == scene->lockedId) {
            scene->pendingState = 0;
            PushPanelState(scene, 0xa);
            return;
        }
        if (id == scene->exclusiveId) {
            scene->pendingState = 1;
            scene->pendingTimer = 1;
            PushPanelState(scene, 6);
            return;
        }
        scene->pendingState = 2;
        PushPanelState(scene, 0xd);
        return;
    case 3:
        if (id == scene->lockedId) {
            scene->pendingState = 0;
            PushPanelState(scene, 0xe);
            return;
        }
        scene->pendingState = 2;
        PushPanelState(scene, 0xd);
        return;
    }
}
