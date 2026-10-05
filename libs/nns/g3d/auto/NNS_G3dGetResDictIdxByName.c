#include "libs/nns/g3d/g3d_kernel_internal.h"

int NNS_G3dGetResDictIdxByName(
    const NNSG3dResDict *dict,
    const NNSG3dResName *name)
{
    if (name == NULL) {
        return -1;
    }

    if (dict->numEntry < 16) {
        u32 index;
        const NNSG3dResName *entryName;
        u32 value0 = name->val[0];
        u32 value1 = name->val[1];
        u32 value2 = name->val[2];
        u32 value3 = name->val[3];

        for (index = 0; index < dict->numEntry; ++index) {
            entryName = NNS_G3dGetResNameByIdx(dict, index);
            if (entryName->val[0] == value0 &&
                entryName->val[1] == value1 &&
                entryName->val[2] == value2 &&
                entryName->val[3] == value3) {
                return (int)index;
            }
        }
    } else {
        const NNSG3dResName *entryName;
        const NNSG3dResDictTreeNode *tree;
        const NNSG3dResDictTreeNode *parent;
        const NNSG3dResDictTreeNode *node;

        tree = &dict->node[0];
        parent = tree;

        if (parent->idxLeft != 0) {
            node = tree + parent->idxLeft;
            while (parent->refBit > node->refBit) {
                parent = node;
                node = tree + *(&node->idxLeft +
                    ((name->val[node->refBit >> 5] >> (node->refBit & 31)) & 1));
            }

            entryName = NNS_G3dGetResNameByIdx(dict, node->idxEntry);
            if (entryName->val[0] == name->val[0] &&
                entryName->val[1] == name->val[1] &&
                entryName->val[2] == name->val[2] &&
                entryName->val[3] == name->val[3]) {
                return node->idxEntry;
            }
        }
    }
    return -1;
}
