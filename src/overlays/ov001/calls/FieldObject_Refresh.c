#include "nitro/types.h"

typedef struct WorkBody {
    u8 pad_00[0x6];
    s16 values[5];
    u8 pad_10[0xcc];
    s16 weights[5];
} WorkBody;

typedef struct ObjectWork {
    u8 pad_00[0x10];
    WorkBody body;
} ObjectWork;

struct FieldObject;

typedef struct FieldObjectClass {
    u8 pad_00[0x14];
    void (*onRefresh)(struct FieldObject *object);
    u8 pad_18[0x4c];
    s16 workIndex;
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    FieldObjectClass *objectClass;
    ObjectWork *work;
    u8 pad_10[0x3e];
    u16 flags;
    u8 pad_50[0x3];
    u8 activeValue;
} FieldObject;

extern BOOL Container_HasFlag3(ObjectWork *work);
extern void func_ov001_0207f71c(FieldObject *object, BOOL enabled);

void FieldObject_Refresh(FieldObject *object)
{
    FieldObjectClass *objectClass = object->objectClass;
    void (*hook)(FieldObject *object);
    WorkBody *body;
    int i;

    if (!(object->flags & 4)) {
        return;
    }
    if (!(object->flags & 0x4000) && objectClass->workIndex >= 0) {
        body = &object->work->body;
        for (i = 0; i < 5; i++) {
            if (body->weights[(u16)i] > 0) {
                object->activeValue = body->values[(u16)i];
                break;
            }
        }
        func_ov001_0207f71c(object, Container_HasFlag3(object->work));
    }
    hook = objectClass->onRefresh;
    if (hook != NULL) {
        hook(object);
    }
}
