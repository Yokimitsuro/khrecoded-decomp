#include "nitro/types.h"

typedef struct GridPos {
    s16 x;
    s16 y;
} __attribute__((aligned(4))) GridPos;

typedef struct MatrixNode {
    u16 index;
    u8 kind;
    u8 pad_03[0x11];
} MatrixNode;

typedef struct MatrixGrid {
    u8 pad_0000[0x18];
    MatrixNode *nodes;
    u8 pad_001c[0x98 - 0x1c];
    u8 *dims;
    MatrixNode *cells[(0x2be8 - 0x9c) / 4];
    u8 requiredLevel[1];
} MatrixGrid;

extern u8 *data_0205fe0c;

extern int GetPackedBitMask(int *bitWords, int bitIndex);
extern BOOL ResolveGridEntry(int x, int y, MatrixGrid *grid, MatrixNode **node);

static inline int GetNodeIndex(MatrixGrid *grid, MatrixNode *node)
{
    if (node >= grid->nodes) {
        return node - grid->nodes;
    }
    return -1;
}

GridPos FindNearestReachableNode(MatrixGrid *grid, GridPos pos, MatrixNode **outNode, BOOL skipCurrent)
{
    u32 width = grid->dims[0];
    MatrixNode *node = grid->cells[pos.x + pos.y * width];
    s16 radius = 1;
    s16 step;
    int index;
    BOOL unlocked;
    u16 nodeIndex;

    if (!skipCurrent) {
        if (node != NULL && node->kind < 14) {
            u8 *ctx = data_0205fe0c;
            if (grid->requiredLevel[node->index] <= ctx[0x2c67]) {
                index = GetNodeIndex(grid, node);
                if (index >= 0) {
                    unlocked = GetPackedBitMask((int *)(ctx + 0x2c5c), index) ? TRUE : FALSE;
                    if (!unlocked) {
                        goto found;
                    }
                }
            }
        }
        for (;;) {
            if (ResolveGridEntry(pos.x, pos.y, grid, &node)) {
                goto found;
            }
            if (ResolveGridEntry(pos.x, pos.y - radius, grid, &node)) {
                goto found;
            }
            if (ResolveGridEntry(pos.x + radius, pos.y, grid, &node)) {
                goto found;
            }
            if (ResolveGridEntry(pos.x - radius, pos.y, grid, &node)) {
                goto found;
            }
            if (ResolveGridEntry(pos.x, pos.y + radius, grid, &node)) {
                goto found;
            }
            for (step = radius; step > 1; step--) {
                if (ResolveGridEntry(pos.x + step, pos.y - radius, grid, &node)
                    || ResolveGridEntry(pos.x - step, pos.y - radius, grid, &node)
                    || ResolveGridEntry(pos.x + radius, pos.y - step, grid, &node)
                    || ResolveGridEntry(pos.x - radius, pos.y - step, grid, &node)
                    || ResolveGridEntry(pos.x + radius, pos.y + step, grid, &node)
                    || ResolveGridEntry(pos.x - radius, pos.y + step, grid, &node)
                    || ResolveGridEntry(pos.x + step, pos.y + radius, grid, &node)
                    || ResolveGridEntry(pos.x - step, pos.y + radius, grid, &node)) {
                    goto found;
                }
            }
            if (ResolveGridEntry(pos.x + radius, pos.y - radius, grid, &node)
                || ResolveGridEntry(pos.x - radius, pos.y - radius, grid, &node)
                || ResolveGridEntry(pos.x + radius, pos.y + radius, grid, &node)
                || ResolveGridEntry(pos.x - radius, pos.y + radius, grid, &node)) {
                goto found;
            }
            radius++;
        }
    }
found:
    if (GetNodeIndex(grid, node) < 0) {
        node = grid->cells[node->index];
    }
    *outNode = node;
    nodeIndex = node->index;
    pos.x = nodeIndex % width;
    pos.y = nodeIndex / width;
    return pos;
}
