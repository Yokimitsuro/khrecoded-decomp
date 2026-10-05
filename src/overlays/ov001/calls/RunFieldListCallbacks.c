#include "nitro/types.h"

typedef struct FieldCallbackNode {
    void (*callback)(void);
} FieldCallbackNode;

typedef struct FieldManager {
    u8 pad_000[0x5d0];
    u8 callbackList[0xc];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 active;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern void *NNS_FndGetNextListObject(void *list, void *obj);

void RunFieldListCallbacks(void)
{
    FieldManager *manager = data_ov001_020a04c4.manager;
    FieldCallbackNode *node;

    if (data_ov001_020a04c4.active == 0) {
        return;
    }
    for (node = NNS_FndGetNextListObject(manager->callbackList, NULL); node != NULL;
         node = NNS_FndGetNextListObject(manager->callbackList, node)) {
        node->callback();
    }
}
