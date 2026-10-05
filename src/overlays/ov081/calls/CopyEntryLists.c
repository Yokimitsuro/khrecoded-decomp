#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))
#define va_arg(ap, type) (*(type *)(((ap) += 4) - 4))
#define va_end(ap) ((void)0)

typedef struct {
    u8 kind;
} EntryList;

typedef struct Ov081State {
    u8 pad_00[0x6120];
    EntryList *entries[110];
} Ov081State;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void CopyEntryLists(Ov081State *state, ...)
{
    va_list args;
    EntryList *source;
    EntryList *copy;
    int i;
    u32 size;

    va_start(args, state);
    for (i = 0; i < 110; i++) {
        source = va_arg(args, EntryList *);
        switch (source->kind) {
        case 0:
            size = 2;
            break;
        case 1:
            size = 8;
            break;
        case 2:
            size = 1;
            break;
        default:
            size = 0;
            break;
        }
        copy = NNSi_FndAllocFromDefaultHeap(size);
        MI_CpuCopy8(source, copy, size);
        state->entries[i] = copy;
    }
    va_end(args);
}
