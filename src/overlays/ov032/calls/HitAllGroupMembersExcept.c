#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 direction;
    u8 attackType;
    u8 pad_0d[3];
    u32 element;
    u8 pad_14[8];
} HitInfo;

typedef struct GroupObject GroupObject;

typedef struct {
    u8 pad_00[0x30];
    BOOL (*isDefeated)(GroupObject *object);
} GroupObjectVtable;

struct GroupObject {
    u8 pad_00[4];
    GroupObjectVtable *vtable;
    u8 pad_08[0x6e];
    u8 hitPending;
    u8 pad_77[0x48];
    u8 hitCooldown;
};

typedef struct {
    u32 firstMember : 9;
    u32 unk_00_9 : 23;
    u8 pad_04[8];
    u16 memberCount : 8;
    u16 unk_0c_8 : 8;
    u8 pad_0e[0x1d2];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

extern const VecFx32 data_0205344c;

extern GroupObject *func_ov001_02086384(FieldContext *context, int index);
extern void *func_ov032_020bbc98(GroupObject *object);
extern void func_01ff88c4(void *dst, u8 value, u32 size);
extern u32 func_ov001_02086408(GroupObject *node, HitInfo *info);

void HitAllGroupMembersExcept(FieldContext *context, int index, GroupObject *except)
{
    FieldObject *object = &context->objects[index];
    HitInfo info;
    int i;

    for (i = 0; i < object->memberCount; i++) {
        GroupObject *member = func_ov001_02086384(context, object->firstMember + i);
        BOOL defeated;
        func_ov032_020bbc98(member);
        if (member->vtable->isDefeated != NULL) {
            defeated = member->vtable->isDefeated(member);
        } else {
            defeated = FALSE;
        }
        if (!defeated && except != member) {
            func_01ff88c4(&info, 0, sizeof(info));
            info.direction = data_0205344c;
            info.attackType = 0;
            info.element = 1;
            member->hitCooldown = 0;
            member->hitPending = 1;
            func_ov001_02086408(member, &info);
        }
    }
}
