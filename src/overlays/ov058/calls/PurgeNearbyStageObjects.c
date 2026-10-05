#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageNode {
    struct StageNode *next;
} StageNode;

extern VecFx32 data_ov058_020d8a4c;

extern BOOL IsFirstEntryFlagSet(void);
extern StageNode *func_ov001_02087264(void);
extern VecFx32 *func_ov001_0208641c(StageNode *node);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void TryEnterFieldUnitPhase5(StageNode *node, int arg);

void PurgeNearbyStageObjects(void)
{
    VecFx32 *center = &data_ov058_020d8a4c;
    StageNode *node;
    VecFx32 *pos;
    fx32 delta;

    if (IsFirstEntryFlagSet()) {
        return;
    }
    for (node = func_ov001_02087264(); node != NULL; node = node->next) {
        pos = func_ov001_0208641c(node);
        if (pos == NULL) {
            continue;
        }
        delta = pos->x - center->x;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta >= 0x8000) {
            continue;
        }
        delta = pos->z - center->z;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta >= 0x8000) {
            continue;
        }
        delta = pos->y - center->y;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta >= 0x8000) {
            continue;
        }
        if (VEC_Distance(pos, center) < 0x8000) {
            TryEnterFieldUnitPhase5(node, 0);
        }
    }
}
