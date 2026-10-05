#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RangeNode RangeNode;
typedef BOOL (*RangeTest)(RangeNode *node, const VecFx32 *point);

typedef struct RangeNodeParams {
    u32 id;
    VecFx32 place;
    s32 shape;
    u8 extent[0xC];
    s32 value;
} RangeNodeParams;

struct RangeNode {
    void *update;
    s32 state;
    void *release;
    s32 value;
    u8 pad_10[2];
    u8 id;
    u8 pad_13;
    RangeTest test;
    u8 extent[0xC];
    VecFx32 place;
};

extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);
extern BOOL IsPointWithinEntityRadius(RangeNode *node, const VecFx32 *point);
extern BOOL IsPointInNodeRange(RangeNode *node, const VecFx32 *point);
extern BOOL IsWithinHorizontalRange(RangeNode *node, const VecFx32 *point);
extern BOOL PointInBox3D(RangeNode *node, const VecFx32 *point);
extern BOOL PointInBoxXZ(RangeNode *node, const VecFx32 *point);
extern void func_ov001_020695b8(void);
extern void func_ov001_02069608(void);

void InitRangeTriggerNode(RangeNode *node, RangeNodeParams *params)
{
    node->place = params->place;
    node->id = params->id;
    node->value = params->value;
    MIi_CpuCopy32(params->extent, node->extent, sizeof(node->extent));
    switch (params->shape) {
    case 0:
        node->test = IsPointWithinEntityRadius;
        break;
    case 1:
        node->test = IsPointInNodeRange;
        break;
    case 2:
        node->test = IsWithinHorizontalRange;
        break;
    case 3:
        node->test = PointInBox3D;
        break;
    case 4:
        node->test = PointInBoxXZ;
        break;
    }
    node->update = func_ov001_020695b8;
    node->state = 0;
    node->release = func_ov001_02069608;
}
