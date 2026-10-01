#define NULL ((void *)0)
typedef unsigned short u16;
typedef struct ResCacheEntry {
    u16 refCount;
    char reserved02[0x12];
    char name[0x20];
} ResCacheEntry;
extern ResCacheEntry *gFileLoader[];
extern int func_02021fbc(const char *left, const char *right);
#define strcmp func_02021fbc

ResCacheEntry *ResCache_FindSlot(const char *key)
{
    struct {
        ResCacheEntry *base;
        u16 refCount;
    } cursor[1];
    int cursorIndex = 0;
    int index;
    ResCacheEntry *unused;
    unsigned int keyIsId = (unsigned int)key & 0x80000000;

    unused = NULL;
    cursor[cursorIndex].base = gFileLoader[2];

    for (index = 0; index < 0xb0; index++) {
        ResCacheEntry *entry = &cursor[cursorIndex].base[index];
        cursor[cursorIndex].refCount = entry->refCount;

        if (cursor[cursorIndex].refCount != 0) {
            unsigned int id = *(unsigned int *)entry->name;
            unsigned int entryIsId = id & 0x80000000;

            if (keyIsId != 0 && entryIsId != 0) {
                if ((unsigned int)key == id)
                    return entry;
            }
            if (keyIsId == 0 && entryIsId == 0) {
                if (strcmp(entry->name, key) == 0)
                    return entry;
            }
        }
        if (cursor[cursorIndex].refCount == 0)
            unused = entry;
    }
    return unused;
}