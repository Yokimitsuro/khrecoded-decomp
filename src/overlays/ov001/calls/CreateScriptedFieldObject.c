#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct FieldObjectClass {
    u8 pad_00[0x70];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7D[0x10];
    s8 blendIndex;
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectClass *def;
    u8 pad_0C[0x08];
    void (*handler)();
    CollisionShape shape;
    u8 pad_38[0x03];
    u8 unk_3B_lo : 4;
    u8 layer : 4;
    u8 pad_3C[0x04];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u16 saveBitOffset;
    u8 saveBitCount;
    s8 blendIndex;
    s32 unk_54;
    u8 isRunning;
    s8 configFlags;
    u8 pad_5A[0x0A];
    char eventLabel[8];
    char scriptName[8];
    u32 unk_74;
    VecFx32 anchor;
} FieldObject;

extern FieldObject *FieldObject_Create(FieldObjectClass *objectClass, u8 slotIndex);
extern int strlen(const char *str);
extern char *strcpy(char *dst, const char *src);
extern void UpdateTurningFieldObject();
extern void BuildCollisionShape(CollisionShape *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int unused);

FieldObject *CreateScriptedFieldObject(FieldObjectClass *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, u16 angle, s8 configFlags, const char *eventLabel, const char *scriptName, u32 unk74, u32 unused, u8 layer)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);
    FieldObjectClass *def = object->def;

    object->position = *position;
    object->angle = angle;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->blendIndex = objectClass->blendIndex;
    object->unk_54 = 0x800;
    object->unk_74 = unk74;
    object->anchor = object->position;
    object->layer = layer;
    if (eventLabel == NULL && scriptName == NULL) {
        object->eventLabel[0] = object->scriptName[0] = 0;
    } else {
        if (eventLabel == NULL) {
            object->eventLabel[0] = 0;
        } else {
            strlen(eventLabel);
            strcpy(object->eventLabel, eventLabel);
        }
        strlen(scriptName);
        strcpy(object->scriptName, scriptName);
    }
    if (configFlags < 0) {
        object->configFlags = 0x80;
    }
    object->handler = UpdateTurningFieldObject;
    object->stateFlags |= 0x10;
    object->stateFlags |= 0x20;
    BuildCollisionShape(&object->shape, &object->position, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, TRUE, 3);
    object->isRunning = FALSE;
    return object;
}
