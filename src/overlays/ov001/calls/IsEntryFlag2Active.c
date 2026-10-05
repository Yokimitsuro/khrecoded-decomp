#include "nitro/types.h"

typedef struct Entry Entry;

struct Entry {
    u8 pad[0x21c];
    u32 (*getFlags)(Entry *entry);
};

extern BOOL func_ov001_020645c8(u32 value);
extern Entry *GetBoundedEntryField(int index);

static inline u32 GetEntryFlags(Entry *entry) {
    if (entry->getFlags != NULL) {
        return entry->getFlags(entry);
    }
    return 0;
}

BOOL IsEntryFlag2Active(int index) {
    Entry *entry;
    if (func_ov001_020645c8(0x3525) == FALSE) {
        entry = GetBoundedEntryField(index);
        if (entry != NULL && (GetEntryFlags(entry) & 2)) {
            return TRUE;
        }
    }
    return FALSE;
}
