#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *field_08;
    u8 pad_0c[0x820 - 0xc];
    void *field_820;
} ActorRegistry;

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void FreeRecordArrayAndReset(void *table);
extern ActorRegistry *data_0206083c;

BOOL ShutdownActorRegistry(void) {
    ActorRegistry *table = data_0206083c;
    if (table != NULL) {
        if (table->field_820 != NULL) {
            NNSi_FndFreeFromDefaultHeap(table->field_820);
            table->field_820 = NULL;
        }
        FreeRecordArrayAndReset(table);
        if (table->field_08 != NULL) {
            NNSi_FndFreeFromDefaultHeap(table->field_08);
        }
        NNSi_FndFreeFromDefaultHeap(table);
        data_0206083c = NULL;
    }
    return TRUE;
}
