#include "nitro/types.h"

typedef struct EffectNode EffectNode;
typedef void *(*EffectUpdate)(EffectNode *node);

struct EffectNode {
    EffectNode *next;
    u8 pad_04[8];
    EffectUpdate update;
};

typedef struct EffectManager {
    u8 pad_00[5];
    u8 flags;
    u8 pad_06[2];
    EffectNode *nodes;
} EffectManager;

extern EffectManager *data_ov001_020a04fc;
extern void ResetLinkedActorOffsets(void);
extern BOOL IsFirstEntryFlagSet(void);
extern void func_ov001_0208707c(int enable);
extern int func_ov001_02067ed4(void);
extern BOOL IsNodeFlagBitClear(EffectNode *node);

void UpdateEffectManager(void)
{
    EffectManager *manager = data_ov001_020a04fc;
    EffectNode *node;
    EffectNode *next;
    EffectUpdate update;

    if (manager->flags & 0x80) {
        ResetLinkedActorOffsets();
        data_ov001_020a04fc->flags &= 0x7f;
    }
    if (data_ov001_020a04fc->flags & 0x51) {
        if (!IsFirstEntryFlagSet() && (data_ov001_020a04fc->flags & 0x40)) {
            func_ov001_0208707c(0);
        }
        return;
    }
    if (func_ov001_02067ed4() < 0) {
        return;
    }
    for (node = manager->nodes; node != NULL; node = next) {
        next = node->next;
        if (IsNodeFlagBitClear(node) && node->update != NULL) {
            update = node->update(node);
            if (update != NULL) {
                node->update = update;
            }
        }
    }
}
