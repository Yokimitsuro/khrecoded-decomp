#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c8];
    void *entry;
} HandlerTable;

extern int func_0202c44c(void);
extern int func_0202c8bc(void *slot);

void func_02026974(HandlerTable *table, s32 index)
{
    if (index >= 0) {
        func_0202c44c();
        func_0202c8bc(*(void **)((u8 *)table->entry + 8));
    }
}
