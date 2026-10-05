#include "nitro/types.h"

typedef struct TagSlot {
    u16 tag;
    u16 pad_02;
    u32 unk_04;
} TagSlot;

typedef struct TagHeader {
    u32 unk_00;
    u16 unk_04;
    u16 count;
} TagHeader;

typedef struct TagTable {
    u32 unk_00;
    u32 unk_04;
    TagSlot slots[1];
} TagTable;

typedef struct TagListOwner {
    u32 unk_00;
    union {
        TagHeader * volatile header;
        TagTable * volatile table;
    } u;
} TagListOwner;

extern TagListOwner *func_ov001_02073060(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void RegisterTaggedEntry(u16 tag);

void RegisterOverlay053TaggedEntries(void)
{
    TagListOwner *owner = func_ov001_02073060();
    int i;

    if (owner != NULL && !func_ov001_020645c8(0x360b)) {
        for (i = 0; i < owner->u.header->count; i++) {
            RegisterTaggedEntry(owner->u.table->slots[i].tag);
        }
    }
}
