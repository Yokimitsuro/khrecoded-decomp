#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x27fc];
    s8 activeMarker;
} Session;

typedef struct ObjectData {
    u8 pad_00[0x64];
    s16 workIndex;
    u8 pad_66[0x1e];
    u8 camera[0x38];
    s8 targetIndex;
} ObjectData;

typedef struct ObjectModel {
    u8 pad_00[0x14];
    u8 node[1];
} ObjectModel;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectData *data;
    ObjectModel *model;
    u8 pad_10[0x2a];
    u8 index;
} FieldObject;

extern Session *data_ov001_020a0480;
extern int func_ov001_02067ed4(void);
extern void DrawNodeWithExplicitProjection(void *node, void *camera, int top, int bottom, int left, int right);

void FieldObject_DrawTargetView(FieldObject *object)
{
    ObjectData *data = object->data;

    if (data->workIndex >= 0 && data->targetIndex == object->index) {
        Session *session = data_ov001_020a0480;

        if (session->activeMarker == -1) {
            session->activeMarker = func_ov001_02067ed4();
        }
        DrawNodeWithExplicitProjection(object->model->node, data->camera, 0xf5c, -0xf5c, -0x147b, 0x147b);
    }
}
