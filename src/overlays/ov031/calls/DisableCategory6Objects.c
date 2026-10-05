#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5a];
    u8 category;
} ObjectInfo;

typedef struct {
    u32 unk_00;
    ObjectInfo *info;
} FieldObject;

typedef struct {
    u8 pad_00[0x3e];
    u16 objectCount;
} FieldLayer;

extern int func_ov001_0208722c(void);
extern FieldLayer *func_ov001_0208723c(int index);
extern FieldObject *func_ov001_02086384(FieldLayer *layer, int index);
extern void func_ov018_020a335c(FieldObject *object, int disabled);

void DisableCategory6Objects(void)
{
    int layerCount = func_ov001_0208722c();
    int i;
    int j;
    FieldLayer *layer;
    FieldObject *object;

    for (i = 0; i < layerCount; i++) {
        layer = func_ov001_0208723c(i);
        if (layer == NULL) {
            return;
        }
        for (j = 0; j < layer->objectCount; j++) {
            object = func_ov001_02086384(layer, j);
            switch (object->info->category) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                break;
            case 6:
                func_ov018_020a335c(object, 1);
                break;
            }
        }
    }
}

