#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void func_ov017_020a4f98(void *dst, const char *format, u32 flags, void *args);
extern void ProcessListHeadIfEmpty(void *obj, void *header);

void FormatAndQueueMessage(void *obj, const char *format, u32 flags, void *args)
{
    void *header = NNSi_FndAllocFromDefaultHeap(8);

    func_ov017_020a4f98(header, format, flags | 4, args);
    ProcessListHeadIfEmpty(obj, header);
}
