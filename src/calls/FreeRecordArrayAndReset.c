#include "nitro/types.h"

typedef struct {
    u16 unk_00;
    u16 count;
    void **entries;
} RecordArray;

extern void MSL_FpInitD(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Frees each entry, then the array itself. */
void FreeRecordArrayAndReset(RecordArray *table) {
    int i = 0;
    if (i < table->count) {
        do {
            if (table->entries[i] != 0) {
                MSL_FpInitD();
                table->entries[i] = 0;
            }
            i++;
        } while (i < table->count);
    }
    if (table->entries != 0) {
        NNSi_FndFreeFromDefaultHeap(table->entries);
        table->entries = 0;
    }
    table->count = 0;
    table->unk_00 = 0;
}
