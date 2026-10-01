typedef unsigned short u16;

typedef struct MBlock {
    u16 value;
    u16 flags;
    int size;
    struct MBlock *previous;
    struct MBlock *next;
} MBlock;

typedef struct MBlockList {
    MBlock *first;
    char *end;
} MBlockList;

MBlock *InitMBlock(MBlockList *list, u16 value)
{
    MBlock *block = list->first;
    char *end = list->end;

    block->value = value;
    block->flags = 0;
    block->size = end - ((char *)block + sizeof(MBlock));
    block->previous = 0;
    block->next = 0;
    return block;
}