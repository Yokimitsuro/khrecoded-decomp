#include "nitro/types.h"

typedef struct ModelObject {
    u8 pad_00[0x78];
    void *model;
    u8 pad_7C[0x130 - 0x7C];
    s32 isActive;
} ModelObject;

extern void NNS_G3dMdlSetMdlPolygonID(void *model, u32 materialIndex, int polygonId);
extern void func_01ffb12c(ModelObject *object);

void ApplyModelPolygonId(ModelObject *object, int polygonBase) {
    if (object->isActive == 0) {
        return;
    }
    NNS_G3dMdlSetMdlPolygonID(object->model, 3, polygonBase + 0x14);
    func_01ffb12c(object);
}
