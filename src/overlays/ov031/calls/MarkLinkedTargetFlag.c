#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 flags;
} LinkTarget;

typedef struct {
    LinkTarget *target;
    s32 type;
} LinkParent;

typedef struct {
    LinkParent *parent;
    s32 type;
} LinkNode;

void MarkLinkedTargetFlag(void *arg0, void *arg1, void *arg2, LinkNode *node)
{
    if (node != NULL && node->type == 2 && node->parent->type == 2) {
        node->parent->target->flags |= 0x2000;
    }
}
