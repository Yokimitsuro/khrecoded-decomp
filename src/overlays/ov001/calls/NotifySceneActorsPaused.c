#include "nitro/types.h"

typedef struct SceneActor SceneActor;
typedef void (*SceneActorHandler)(SceneActor *actor, int event, int arg);

struct SceneActor {
    u8 pad_000[0x20c];
    SceneActorHandler handler;
};

typedef struct SceneActorEntry {
    u8 pad_00[8];
    SceneActor *actor;
    u8 pad_0c[0x1c];
} SceneActorEntry;

typedef struct SceneActorList {
    SceneActorEntry entries[3];
    u8 pad_78[4];
    int count;
} SceneActorList;

extern SceneActorList *data_ov001_020a04bc;

void NotifySceneActorsPaused(BOOL paused)
{
    SceneActorList *list = data_ov001_020a04bc;
    int i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        SceneActor *actor = list->entries[i].actor;

        if (actor != NULL) {
            if (paused) {
                if (actor->handler != NULL) {
                    actor->handler(actor, 3, 1);
                }
            } else {
                if (actor->handler != NULL) {
                    actor->handler(actor, 3, 0);
                }
            }
        }
    }
}


