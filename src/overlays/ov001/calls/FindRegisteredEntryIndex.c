#include "nitro/types.h"

typedef struct {
    void **entries;
    s8 count;
} Registry;

extern Registry *data_ov001_020a04f8;

int FindRegisteredEntryIndex(void *value) {
    int i = 0;
    while (i < data_ov001_020a04f8->count) {
        if (data_ov001_020a04f8->entries[i] == value) {
            return i;
        }
        i++;
    }
    return -1;
}
