#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_01;
    u16 count;
    u16 maxCount;
} OverlaySelectionRecord;

extern u8 data_020608c8;
extern OverlaySelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);

void AddToSelectionCounters(int amount) {
    int index;
    for (index = 0; index < data_020608c8; index++) {
        OverlaySelectionRecord *record = GetOverlaySelectionRecord(index);
        int value = record->count + amount;
        int limit = record->maxCount;
        if (limit > value) {
            limit = value;
        }
        record->count = limit;
    }
}
