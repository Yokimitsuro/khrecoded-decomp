#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*ObjectFunc)(void);

typedef struct FieldObject {
    ObjectFunc init;
    ObjectFunc release;
    ObjectFunc update;
    ObjectFunc destroy;
    ObjectFunc releaseChild;
    u8 pad_14[4];
    ObjectFunc reset;
    ObjectFunc onTouch;
    ObjectFunc onIdle;
    ObjectFunc setPosition;
    ObjectFunc getAnchor;
    ObjectFunc beginSpawn;
    ObjectFunc load;
    ObjectFunc getCenter;
    ObjectFunc onHit;
    ObjectFunc draw;
    u8 pad_40[0xc];
    fx32 radius;
    s32 state;
    u8 pad_54[0x10];
    u16 soundId;
    u8 pad_66[0xa];
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
    u8 kind;
    u8 layer;
    u8 pad_7e[4];
    u8 hidden;
    u8 pad_83;
    s32 timer;
} FieldObject;

extern FieldObject *func_ov001_0207f3a8(int headerSize, int width, int height);
extern void func_ov001_0207f0f8(void);
extern void func_ov001_0207f150(void);
extern void FieldObject_LoadAndPlace(void);
extern void func_ov001_0207f210(void);
extern void func_ov011_020a0930(void);
extern void func_ov001_0207f26c(void);
extern void func_ov011_020a096c(void);
extern void func_ov011_020a0970(void);
extern void FieldObject_SetPositionAndSync(void);
extern void FieldObject_BeginSpawn(void);
extern void FieldObject_HandleContact(void);
extern void func_ov011_020a0fc0(void);
extern void FieldObject_Draw(void);

FieldObject *FieldObject_Create_020a0fc4(int height)
{
    FieldObject *object = func_ov001_0207f3a8(0x18c, 0x68, height);

    object->state = 0;
    object->kind = 3;
    object->scaleX = 0x1800;
    object->scaleY = 0x1800;
    object->scaleZ = 0x1800;
    object->soundId = 0xbb;
    object->hidden = 0;
    object->radius = 0x3000;
    object->init = func_ov001_0207f0f8;
    object->release = func_ov001_0207f150;
    object->update = FieldObject_LoadAndPlace;
    object->destroy = func_ov001_0207f210;
    object->releaseChild = func_ov011_020a0930;
    object->reset = func_ov001_0207f26c;
    object->onTouch = NULL;
    object->onIdle = func_ov011_020a096c;
    object->getAnchor = func_ov011_020a0970;
    object->setPosition = FieldObject_SetPositionAndSync;
    object->beginSpawn = FieldObject_BeginSpawn;
    object->onHit = NULL;
    object->load = FieldObject_HandleContact;
    object->getCenter = func_ov011_020a0fc0;
    object->draw = FieldObject_Draw;
    object->layer = 0xe;
    object->timer = 0;
    return object;
}
