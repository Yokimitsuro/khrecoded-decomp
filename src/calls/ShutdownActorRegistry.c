#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *field_08;
    u8 pad_0c[0x820 - 0xc];
    void *field_820;
} ActorRegistry;

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void FreeRecordArrayAndReset(void *table);
extern ActorRegistry *gActorRegistry;

BOOL ShutdownActorRegistry(void) {
    ActorRegistry *table = gActorRegistry;
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
        gActorRegistry = NULL;
    }
    return TRUE;
}
