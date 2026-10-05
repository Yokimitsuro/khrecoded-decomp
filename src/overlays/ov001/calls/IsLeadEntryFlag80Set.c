#include "nitro/types.h"

typedef struct Entry Entry;

struct Entry {
    u8 pad_000[0x21c];
    u32 (*getFlags)(Entry *entry);
};

extern Entry *GetBoundedEntryField(int index);

BOOL IsLeadEntryFlag80Set(void)
{
    BOOL result = FALSE;
    Entry *entry = GetBoundedEntryField(0);
    u32 flags;

    if (entry != NULL) {
        if (entry->getFlags != NULL) {
            flags = entry->getFlags(entry);
        } else {
            flags = 0;
        }
        if (flags & 0x80) {
            result = TRUE;
        }
    }
    return result;
}
