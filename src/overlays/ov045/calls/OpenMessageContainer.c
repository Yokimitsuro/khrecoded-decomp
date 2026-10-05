#include "nitro/types.h"

extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern u32 func_0202c378(u32 fileId, u32 param2);

void OpenMessageContainer(void **outHeader, u32 *outHandle, const char *name, u32 slot)
{
    void *header = Msg_OpenContainerAndReadHeader(name, 0xe, FALSE);

    *outHeader = header;
    *outHandle = func_0202c378(0x80000000 | ((((u32)header + 0x8000) & 0xfffffc) << 7) | (slot & 0x1ff), 0xe);
}
