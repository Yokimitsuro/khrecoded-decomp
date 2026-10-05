#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *buffer;
    u8 pad_10[0x8c];
    u32 pad_9c_bits : 31;
    u32 ownsBuffer : 1;
} BufferHolder;

extern void func_ov001_0209cf90(void *block);

void FreeOwnedBuffer(BufferHolder *holder)
{
    if (holder->ownsBuffer && holder->buffer != NULL) {
        func_ov001_0209cf90(holder->buffer);
    }
    holder->buffer = NULL;
}
