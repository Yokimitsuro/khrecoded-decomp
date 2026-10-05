#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5a];
    u8 kind;
} ObjectInfo;

typedef struct FieldObject FieldObject;

struct FieldObject {
    FieldObject *next;
    ObjectInfo *info;
};

extern FieldObject *func_ov001_02087264(void);
extern void func_ov018_020a37d0(FieldObject *object);

void FlagKind6Objects(void)
{
    FieldObject *object;

    for (object = func_ov001_02087264(); object != NULL; object = object->next) {
        if (object->info->kind == 6) {
            func_ov018_020a37d0(object);
        }
    }
}
