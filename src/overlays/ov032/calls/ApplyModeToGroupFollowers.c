#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 unk_08_0 : 13;
    u32 visible : 1;
    u32 savedVisible : 1;
    u32 unk_08_15 : 17;
} RenderNode;

typedef struct {
    u8 pad_00[0x33];
    u8 objectIndex;
    u8 pad_34[0xb8];
    RenderNode *renderNode;
} GroupObject;

typedef struct {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 unk_00_18 : 14;
    u8 pad_04[8];
    u16 memberCount : 8;
    u16 unk_0c_8 : 8;
    u8 pad_0e[0x1d2];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

extern GroupObject *func_ov001_02086384(FieldContext *context, int index);
extern BOOL IsNodeFlagBitClear(GroupObject *object);
extern void func_ov032_020bc208(GroupObject *object, int mode);

void ApplyModeToGroupFollowers(FieldContext *context, int index, int mode, BOOL hide, BOOL restore)
{
    FieldObject *object = &context->objects[index];
    int i;

    for (i = 0; i < object->memberCount; i++) {
        GroupObject *member = func_ov001_02086384(context, object->firstMember + i);
        if (object->leaderIndex != member->objectIndex) {
            if (IsNodeFlagBitClear(member)) {
                func_ov032_020bc208(member, mode);
            }
            if (hide) {
                member->renderNode->savedVisible = member->renderNode->visible;
                member->renderNode->visible = 0;
            } else if (restore) {
                member->renderNode->visible = member->renderNode->savedVisible;
            }
        }
    }
}
