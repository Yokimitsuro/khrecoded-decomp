#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    u8 pad0[0x10];
    Point pos;
    u8 pad18[0x18];
} Entry;

typedef struct {
    Entry *entries;
    int unk4;
    Point base;
    u8 pad10[2];
    s8 activeIndex;
    u8 pad13[0x1c - 0x13];
    int offsetX;
    int dirty;
} Scroller;

extern void func_ov001_0206ad1c(void *arg);

void FlushScrolledEntryPosition(Scroller *scroller) {
    if (scroller->dirty != 0) {
        Entry *entry = &scroller->entries[scroller->activeIndex - 1];
        Point pos = scroller->base;
        pos.x += scroller->offsetX;
        entry->pos = pos;
        func_ov001_0206ad1c(entry);
        scroller->dirty = 0;
    }
}
