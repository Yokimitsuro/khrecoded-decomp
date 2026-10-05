#include "nitro/types.h"

typedef struct SlotEntry {
    u8 pad_00[0x2a];
    u8 frameCount : 5;
    u8 frameFlags : 3;
    u8 pad_2b[0x8c - 0x2b];
    s32 ownerId;
    u8 pad_90[0x9c - 0x90];
} SlotEntry;

typedef struct ActorEntry {
    u8 pad_000[0x24];
    u8 node[0x98 - 0x24];
    int active;
    u8 pad_09c[0x12c - 0x9c];
    int state;
    u8 pad_130[0x138 - 0x130];
} ActorEntry;

typedef struct SceneConfig {
    u8 pad_00[0x4c];
    int brightBackground;
} SceneConfig;

typedef struct SlotScene {
    u8 pad_0000[0x1058];
    u8 camera[0x1090 - 0x1058];
    SlotEntry *slots;
    ActorEntry *actors;
    SceneConfig *config;
    u8 pad_109c[0x10dc - 0x109c];
    int highlight;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;
extern void func_ov001_0206aa7c(void);
extern void func_ov001_0206ad1c(void *arg);
extern void camera_commit_explicit_projection(void *camera, int top, int bottom, int left, int right);
extern void func_01ffb12c(void *node);
extern void G3X_SetClearColor(unsigned color, unsigned alpha, unsigned depth, unsigned polygonId, BOOL fog);

void DrawPanelSceneFrame(void)
{
    SlotScene *scene = data_ov036_020c3940.scene;
    int highlight = 0;
    int i;

    func_ov001_0206aa7c();
    for (i = 0; i < 8; i++) {
        SlotEntry *slot = &scene->slots[i];
        if (slot->ownerId != -1 && slot->frameCount != 0) {
            func_ov001_0206ad1c(slot);
        }
    }
    camera_commit_explicit_projection(data_ov036_020c3940.scene->camera, 0x15ec, -0x15ec, -0x1d1f, 0x1d1f);
    for (i = 0; i < 5; i++) {
        if (scene->actors[i].active != 0) {
            func_01ffb12c(scene->actors[i].node);
            if ((u32)(scene->actors[i].state - 13) <= 1) {
                highlight = 1;
            }
        }
    }
    if (scene->highlight != highlight) {
        scene->highlight = highlight;
        if (scene->config->brightBackground != 0) {
            G3X_SetClearColor(0x7ffe, 0x1f, 0x7fff, 0x3f, FALSE);
        } else {
            G3X_SetClearColor(0, scene->highlight, 0x7fff, 0x3f, FALSE);
        }
    }
}
