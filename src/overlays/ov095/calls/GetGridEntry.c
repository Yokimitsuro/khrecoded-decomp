#include "nitro/types.h"

typedef struct {
    u8 data[0x14];
} GridEntry;

typedef struct {
    u8 pad[0xc9e8];
    GridEntry entries[1];
} GridWork;

GridEntry *GetGridEntry(int disabled, int index, GridWork *work) {
    if (disabled == 0) {
        return &work->entries[index];
    }
    return NULL;
}
