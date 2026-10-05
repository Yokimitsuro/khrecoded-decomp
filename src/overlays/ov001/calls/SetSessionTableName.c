#include "nitro/types.h"

typedef struct NameTable {
    u8 pad_00[0xa];
    u8 count;
    u8 pad_0b;
    char **names;
} NameTable;

typedef struct Session {
    u8 pad_0000[0x27e8];
    NameTable nameTable;
} Session;

extern Session *data_ov001_020a0480;
extern int strlen(const char *s);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern char *strcpy(char *dst, const char *src);

void SetSessionTableName(int index, const char *name) {
    NameTable *table = &data_ov001_020a0480->nameTable;
    int length = strlen(name);
    table->names[index] = NNSi_FndAllocFromDefaultHeap(length + 1);
    strcpy(table->names[index], name);
}
