#include "nitro/types.h"

typedef struct EntryList {
    u8 pad_0000[0x4580];
    u16 filteredCount;
} EntryList;

extern void func_ov085_020c1cdc(EntryList *list, u32 category);

u16 FilterEntriesByCategory(EntryList *list, u32 category) {
    func_ov085_020c1cdc(list, category);
    return list->filteredCount;
}
