#include "nitro/types.h"

typedef struct {
    s16 key;
    u16 value;
} KeyValue;

typedef struct {
    int count;
    KeyValue entries[1];
} KeyValueTable;

typedef struct {
    u8 pad[0x273c];
    KeyValueTable *lookup;
} Session;

extern Session *data_ov001_020a0480;

u16 LookupSessionKeyValue(int key) {
    int i = 0;
    KeyValueTable *table = data_ov001_020a0480->lookup;
    while (i < table->count) {
        if (key == table->entries[i].key) {
            return table->entries[i].value;
        }
        i++;
    }
    return 0;
}
