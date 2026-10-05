#include "nitro/types.h"

typedef struct MenuEntry {
    u32 unk_00;
    u32 vramSlot;
} MenuEntry;

typedef struct MenuData {
    u8 pad_00[0xd0];
    MenuEntry *entries;
} MenuData;

extern MenuData *data_ov001_020a04e4;
extern u32 MakePrimaryVramKey_02071248(u32 slot);
extern void *QueueFileLoadRequest(char *path, int loadMode, void (*callback)(void), void *userData);
extern void func_ov001_02078d7c(void);

void LoadMenuEntryGraphic(void *menu, int index)
{
    QueueFileLoadRequest((char *)MakePrimaryVramKey_02071248(data_ov001_020a04e4->entries[index].vramSlot), 1, func_ov001_02078d7c, NULL);
}
