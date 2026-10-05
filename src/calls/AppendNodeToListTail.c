#include "nitro/types.h"

void AppendNodeToListTail(u32 *node, u32 *newNode)
{
    u32 *tail;
    u32 *next;

    tail = node;
    while ((next = node) != 0) {
        tail = next;
        node = (u32 *)next[6];
    }
    if (tail != 0) {
        newNode[7] = (u32)tail;
        tail[6] = (u32)newNode;
    } else {
        newNode[7] = 0;
    }
}
