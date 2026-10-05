#include "nitro/types.h"

typedef struct StageObject {
    u8 pad_000[0x280];
    u16 id;
} StageObject;

typedef struct StageData {
    u8 pad_00000[0x18d84];
    void *objectPool;
} StageData;

extern StageData *data_ov001_020a0528;
extern void *func_ov001_0208f2a4(void *pool);
extern void *func_ov001_0208f2b4(void *node);
extern StageObject *func_ov001_0208f290(void *pool, void *node);

StageObject *FindStageObjectById(u16 id)
{
    void *pool = data_ov001_020a0528->objectPool;
    void *node = func_ov001_0208f2a4(pool);
    StageObject *object = func_ov001_0208f290(pool, node);

    while (object != NULL) {
        if (object->id == id) {
            return object;
        }
        node = func_ov001_0208f2b4(node);
        if (node == NULL) {
            break;
        }
        object = func_ov001_0208f290(pool, node);
    }
    return NULL;
}
