#include "nitro/types.h"

typedef struct HistoryEntry {
    u8 data[4];
} HistoryEntry;

typedef struct SceneHistory {
    u8 pad_000000[0xb47c2];
    HistoryEntry entries[4];
    u8 head;
    u8 count;
} SceneHistory;

extern SceneHistory *data_0206084c;

HistoryEntry *GetRecentHistoryEntry(int age)
{
    SceneHistory *scene = data_0206084c;

    if (age >= scene->count) {
        return NULL;
    }
    return &scene->entries[(u16)((scene->head + scene->count + 3 - age) % 4)];
}
