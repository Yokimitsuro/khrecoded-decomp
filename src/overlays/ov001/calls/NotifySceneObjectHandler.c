#include "nitro/types.h"

typedef struct SceneObject SceneObject;

typedef struct SceneObjectHandler {
    u8 pad_00[0x14];
    void (*notify)(SceneObject *object, int kind, int value);
} SceneObjectHandler;

struct SceneObject {
    u8 pad_000[0x278];
    SceneObjectHandler *handler;
};

void NotifySceneObjectHandler(SceneObject *object, int value)
{
    if (object != NULL && object->handler != NULL) {
        object->handler->notify(object, 0, value);
    }
}
