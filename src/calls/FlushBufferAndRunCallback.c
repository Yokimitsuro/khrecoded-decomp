#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    void *bufferAddr;
} InnerBlock;

typedef struct {
    u8 pad_00[0x20];
    InnerBlock *block;
    u8 pad_24[4];
    u32 size;
    u16 multiplier1;
    u8 pad_2e[0x32 - 0x2e];
    u8 multiplier2;
    u8 tableIndex;
} Context_0200153c;

extern void DC_FlushRange(void *dst, u32 size);
extern void DC_FlushAll(void);
extern void Callbacks_RunTableEntry(int index, int arg1, int arg2, int arg3);

void FlushBufferAndRunCallback(Context_0200153c *context)
{
    void *bufferAddr = context->block->bufferAddr;

    if (context->size >= 0x2400) {
        DC_FlushAll();
    } else {
        DC_FlushRange(bufferAddr, context->size);
    }
    Callbacks_RunTableEntry(context->tableIndex, (int)context->block->bufferAddr,
                                      context->multiplier2 * context->multiplier1,
                                      context->size);
}
