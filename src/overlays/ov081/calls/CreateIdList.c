#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))
#define va_arg(ap, type) (*(type *)(((ap) += 4) - 4))
#define va_end(ap) ((void)0)

typedef struct {
    u8 kind;
    u8 count;
    u8 pad_02[2];
    u8 *ids;
} EntryList;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

EntryList CreateIdList(int count, ...)
{
    EntryList list;
    va_list args;
    int i;
    int length;

    va_start(args, count);
    list.kind = 1;
    length = count;
    list.count = length;
    list.ids = NNSi_FndAllocFromDefaultHeap(length);
    for (i = 0; i < length; i++) {
        list.ids[i] = va_arg(args, u8);
    }
    va_end(args);
    return list;
}
