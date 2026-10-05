#include "nitro/types.h"

typedef struct QuadTree {
    u8 pad_00[0x84];
    u8 insertionBounds[0x18];
    void *root;
} QuadTree;

extern void QuadTree_Insert(void *root, void *bounds, void *node);

void QuadTree_InsertObject(QuadTree *tree, void *node)
{
    if (tree->root == NULL) {
        return;
    }
    QuadTree_Insert(tree->root, tree->insertionBounds, node);
}
