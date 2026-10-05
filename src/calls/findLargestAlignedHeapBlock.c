extern int abs(int);

typedef struct Block {
    int pad0;
    int payloadSize;
    int pad8;
    struct Block *next;
} Block;

int findLargestAlignedHeapBlock(void *heap, int alignmentInput) {
    int alignment;
    int largestAvailableSize;
    unsigned int bestPadding;
    Block *block;
    unsigned int alignmentMaskLow, alignmentMaskHigh;

    alignment = abs(alignmentInput);
    block = *(Block **)((char *)heap + 0x24);
    largestAvailableSize = 0;
    bestPadding = (unsigned int)-1;
    if (block == 0) goto end;

    alignmentMaskLow = alignment - 1;
    alignmentMaskHigh = ~alignmentMaskLow;
    do {
        unsigned int payloadStart = (unsigned int)block + 0x10;
        unsigned int payloadSize = (unsigned int)block->payloadSize;
        unsigned int alignedStart = (alignmentMaskLow + payloadStart) & alignmentMaskHigh;
        unsigned int payloadEnd = payloadSize + payloadStart;
        if (alignedStart < payloadEnd) {
            unsigned int availableSize = payloadEnd - alignedStart;
            unsigned int padding = alignedStart - payloadStart;
            if ((unsigned int)largestAvailableSize < availableSize ||
                ((unsigned int)largestAvailableSize == availableSize && bestPadding > padding)) {
                largestAvailableSize = availableSize;
                bestPadding = padding;
            }
        }
        block = block->next;
    } while (block);
end:
    return largestAvailableSize;
}
