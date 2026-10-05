#include "nitro/types.h"

typedef struct {
    int *info;
    int kind;
} HitEntry;

BOOL IsHitEntryAccepted(int unused, HitEntry *entry) {
    if (entry != NULL) {
        if (entry->kind == 2 && (u32)entry->info[1] <= 1) {
            return TRUE;
        }
        if (entry->kind == 0x20) {
            return TRUE;
        }
    }
    return FALSE;
}
