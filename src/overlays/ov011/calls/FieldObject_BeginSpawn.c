#include "nitro/types.h"

typedef struct ObjectClass {
    u8 pad_00[0x50];
    s32 result;
} ObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectClass *objectClass;
    u8 pad_0c[0x34];
    u32 position[3];
    u8 pad_4c[0x10];
    u8 spawnCommand[4];
} FieldObject;

extern void func_ov011_020a0708(FieldObject *object, int state);
extern void func_ov011_020a0b1c(void *command, FieldObject *object);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, u32 *position, u32 flags);

s32 FieldObject_BeginSpawn(FieldObject *object)
{
    ObjectClass *objectClass = object->objectClass;
    func_ov011_020a0708(object, 1);
    func_ov011_020a0b1c(object->spawnCommand, object);
    SpawnSoundSlot(0, 0x2d, object->position, 0);
    return objectClass->result;
}
