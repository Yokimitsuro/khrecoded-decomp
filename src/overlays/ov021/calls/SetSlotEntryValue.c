#include "nitro/types.h"

typedef struct {
    u8 pad_000[4];
    u16 value;
    u8 pad_006[0x132];
} SlotEntry;

typedef struct {
    SlotEntry *entries;
} SlotTable;

extern void *data_ov021_020b5628;

extern SlotTable *func_ov021_020a8830(void *owner, void *manager);

void SetSlotEntryValue(void *owner, int slot, u16 value) {
    SlotTable *table;

    if (data_ov021_020b5628 != NULL && (table = func_ov021_020a8830(owner, data_ov021_020b5628)) != NULL) {
        table->entries[slot].value = value;
    }
}
