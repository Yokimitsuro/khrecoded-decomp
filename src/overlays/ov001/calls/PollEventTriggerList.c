#include "nitro/types.h"

typedef struct TriggerCallback {
    BOOL (*test)(struct TriggerCallback *callback);
} TriggerCallback;

typedef struct TriggerNode {
    u8 pad_00[4];
    struct TriggerNode *next;
    TriggerCallback callback;
    u8 pad_0C[0x44];
    u16 eventId;
    u8 state;
    u8 config;
} TriggerNode;

typedef struct TriggerList {
    u8 pad_00[4];
    TriggerNode *head;
} TriggerList;

typedef struct TriggerScene {
    u16 firedIds[8];
    s8 firedCount;
    u8 active;
    u8 pad_12[0x22];
    TriggerList *list;
} TriggerScene;

typedef void *(*SceneStep)(void);

extern TriggerScene *NNSi_FndGetCurrentRootHeap(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void *func_ov001_02068f4c(void);

SceneStep PollEventTriggerList(void)
{
    TriggerScene *scene = NNSi_FndGetCurrentRootHeap();
    TriggerCallback *callback;
    TriggerNode *node;

    if (!scene->active) {
        return (SceneStep)func_ov001_02068f4c;
    }
    for (node = scene->list->head; node != NULL; node = node->next) {
        callback = &node->callback;
        if (!func_ov001_020645c8(node->eventId * 2 + 0x331F) && callback->test != NULL && (node->config & 1)
            && !(node->state & 1) && callback->test(callback)) {
            scene->firedIds[scene->firedCount] = node->eventId;
            node->state |= 1;
            scene->firedCount++;
        }
    }
    return NULL;
}
