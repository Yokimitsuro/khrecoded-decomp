#ifndef GFDI_LINKED_LIST_VRAM_MAN_COMMON_H
#define GFDI_LINKED_LIST_VRAM_MAN_COMMON_H

typedef unsigned int u32;
typedef int BOOL;

#define GFD_NULL ((void *)0)
#define GFD_TRUE 1
#define GFD_FALSE 0

typedef struct NNSiGfdLnkVramBlock NNSiGfdLnkVramBlock;

struct NNSiGfdLnkVramBlock {
    u32 address;
    u32 size;
    NNSiGfdLnkVramBlock *previous;
    NNSiGfdLnkVramBlock *next;
};

typedef struct NNSiGfdLnkVramMan {
    NNSiGfdLnkVramBlock *freeList;
} NNSiGfdLnkVramMan;

typedef struct NNSiGfdLnkMemRegion {
    u32 start;
    u32 end;
} NNSiGfdLnkMemRegion;

static inline void InitBlockFromRegion_(NNSiGfdLnkVramBlock *block, const NNSiGfdLnkMemRegion *region)
{
    block->address = region->start;
    block->size = region->end - region->start;
    block->previous = GFD_NULL;
    block->next = GFD_NULL;
}

static inline void InitBlockFromParams_(NNSiGfdLnkVramBlock *block, u32 address, u32 size)
{
    block->address = address;
    block->size = size;
    block->previous = GFD_NULL;
    block->next = GFD_NULL;
}

static inline void InsertBlock_(NNSiGfdLnkVramBlock **listHead, NNSiGfdLnkVramBlock *block)
{
    if (*listHead != GFD_NULL) {
        (*listHead)->previous = block;
    }
    block->next = *listHead;
    block->previous = GFD_NULL;
    *listHead = block;
}

static inline void RemoveBlock_(NNSiGfdLnkVramBlock **listHead, NNSiGfdLnkVramBlock *block)
{
    NNSiGfdLnkVramBlock *const previous = block->previous;
    NNSiGfdLnkVramBlock *const next = block->next;

    if (previous) {
        previous->next = next;
    } else {
        *listHead = next;
    }
    if (next) {
        next->previous = previous;
    }
}

static inline NNSiGfdLnkVramBlock *GetNewBlock_(NNSiGfdLnkVramBlock **blockPoolList)
{
    NNSiGfdLnkVramBlock *block = *blockPoolList;
    if (block) {
        *blockPoolList = block->next;
    }
    return block;
}

static inline u32 GetBlockEndAddress_(NNSiGfdLnkVramBlock *block)
{
    return block->address + block->size;
}

#endif
