#include "nitro/types.h"

typedef struct Entry Entry;

struct Entry {
    u8 pad[0x21c];
    u32 (*getFlags)(Entry *entry);
};

typedef struct {
    u8 pad[8];
    Entry *entry;
} Holder;

extern Holder *data_ov001_020a04bc;
extern u32 GetBoundedEntryField(int index);

static inline u32 GetEntryFlags(Entry *entry) {
    if (entry->getFlags != NULL) {
        return entry->getFlags(entry);
    }
    return 0;
}

BOOL IsHeldEntryFlag2Active(void) {
    Holder *holder = data_ov001_020a04bc;
    BOOL result = FALSE;
    if (holder == NULL) {
        return result;
    }
    if (GetBoundedEntryField(0) != 0 && (GetEntryFlags(holder->entry) & 2)) {
        result = TRUE;
    }
    return result;
}
