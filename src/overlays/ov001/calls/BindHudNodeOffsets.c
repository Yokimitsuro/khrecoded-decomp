#include "nitro/types.h"

typedef struct NodeOffset {
    s32 x;
    s32 y;
} NodeOffset;

typedef struct HudNode {
    u8 pad_00[0x10];
    NodeOffset pos;
    u8 pad_18[8];
    s32 scale;
    u8 pad_24[0xC];
} HudNode;

typedef struct NodeIndices {
    s32 index[4];
} NodeIndices;

typedef struct NodeOffsets {
    NodeOffset offset[4];
} NodeOffsets;

typedef struct HudBinding {
    u32 unk_00;
    HudNode *nodes[4];
    u8 pad_14[4];
    HudNode *nodeA;
    HudNode *nodeB;
} HudBinding;

extern const NodeIndices data_ov001_0209e078;
extern const NodeOffsets data_ov001_0209e0a8;

extern HudNode *func_ov001_0206dc20(void);

void BindHudNodeOffsets(HudBinding *binding)
{
    NodeIndices indices = data_ov001_0209e078;
    HudNode *base = func_ov001_0206dc20();
    NodeOffsets offsets = data_ov001_0209e0a8;
    int i;

    if (base != NULL) {
        for (i = 0; i < 4; i++) {
            binding->nodes[i] = &base[indices.index[i]];
            binding->nodes[i]->pos = offsets.offset[i];
            binding->nodes[i]->scale = 0x800;
        }
        binding->nodeA = &base[6];
        binding->nodeB = &base[5];
        binding->nodeA->scale = 0x1000;
        binding->nodeB->scale = 0;
    }
}
