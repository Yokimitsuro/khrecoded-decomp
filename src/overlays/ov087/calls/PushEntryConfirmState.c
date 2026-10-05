#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    int kind;
    int unk_04;
} PanelMode;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[8];
    u8 pad_958[0x218];
    PanelMode modes[6];
    int modeIndex;
    u8 pad_ba4[0x1c];
    int pendingState;
    int pendingTimer;
} PanelScene;

extern void PushPanelState(PanelScene *scene, int stateId);

void PushEntryConfirmState(PanelScene *scene)
{
    u32 id = scene->entries[scene->cursor].id;
    int kind = scene->modes[scene->modeIndex].kind;

    switch (kind) {
    case 1:
    case 2:
    case 3:
        if (id == 6) {
            PushPanelState(scene, 0xc);
        } else {
            PushPanelState(scene, 0xb);
        }
        scene->pendingState = 3;
        scene->pendingTimer = 0;
        break;
    }
}

