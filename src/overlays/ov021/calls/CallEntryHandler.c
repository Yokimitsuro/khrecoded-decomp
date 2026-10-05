#include "nitro/types.h"

typedef struct HandlerEntry HandlerEntry;

struct HandlerEntry {
    u8 pad_000[0x1f0];
    int (*handler)(HandlerEntry *entry, int a, int b, int c);
};

extern HandlerEntry *GetBoundedEntryField(int index);

int CallEntryHandler(int index, int a, int b, int c) {
    HandlerEntry *entry = GetBoundedEntryField(index);

    if (entry->handler != NULL) {
        return entry->handler(entry, a, b, c);
    }
    return -1;
}
