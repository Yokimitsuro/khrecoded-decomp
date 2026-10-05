#include "nitro/types.h"

typedef void (*RefreshFunc)(void *object, int first, int second);

typedef struct MenuObject {
    u8 pad[0x20c];
    RefreshFunc refresh;
} MenuObject;

typedef struct MenuEntry {
    u32 unk0;
    MenuObject *object;
    u8 pad[0x1c];
    u16 flags;
    u16 unk26;
} MenuEntry;

typedef struct MenuList {
    u32 unk0;
    MenuEntry entries[3];
    int count;
} MenuList;

extern MenuList *data_ov001_020a04bc;
extern int func_ov001_02063a38(void);
extern void SetMenuHighlight(BOOL enable);
extern void func_ov001_0206cab4(int enabled);

void RefreshMenuEntries(void) {
    MenuList *list = data_ov001_020a04bc;
    MenuEntry *entry;
    RefreshFunc refresh;
    int i;

    if (list != NULL) {
        if (func_ov001_02063a38() != 7) {
            SetMenuHighlight(1);
        }
        func_ov001_0206cab4(1);
        for (i = 0; i < list->count; i++) {
            entry = &list->entries[i];
            if (entry->object != NULL) {
                entry->flags |= 4;
                refresh = entry->object->refresh;
                if (refresh != NULL) {
                    refresh(entry->object, 1, 1);
                }
            }
        }
    }
}
