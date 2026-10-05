#include "nitro/types.h"

extern u32 OS_DisableIrqMask(u32 mask);
extern u32 OS_EnableIrqMask(u32 mask);

/* Unlinks a node from a doubly linked list. */
u32 *UnlinkNodeIrqSafe(u32 *listHead, u32 irqMask, u32 *node) {
    u32 *next;
    u32 *prev;

    OS_DisableIrqMask(irqMask);
    prev = (u32 *)node[7];
    next = (u32 *)node[6];
    if (prev != 0) {
        *(u32 *)((u32)prev + 0x18) = (u32)next;
    }
    if (next != 0) {
        *(u32 *)((u32)next + 0x1c) = (u32)prev;
    }
    *node = 0;
    if (node == listHead) {
        listHead = (u32 *)node[6];
    }
    OS_EnableIrqMask(irqMask);
    return listHead;
}
