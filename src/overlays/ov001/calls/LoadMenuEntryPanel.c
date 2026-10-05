#include "nitro/types.h"

typedef struct MenuEntry {
    u32 vramSlot;
    u32 unk_04;
} MenuEntry;

typedef struct MenuData {
    u8 pad_00[0xd0];
    MenuEntry *entries;
} MenuData;

typedef struct MenuLoader {
    u8 pad_00[8];
    int state;
} MenuLoader;

extern MenuData *data_ov001_020a04e4;
extern u32 func_ov001_02071248(u32 slot);
extern void *func_ov027_020ba134(char *path, int loadMode, void (*callback)(void), void *userData);
extern void LoadModeBg1Characters(void);

void LoadMenuEntryPanel(MenuLoader *loader, int index)
{
    u32 slot = data_ov001_020a04e4->entries[index].vramSlot;

    loader->state = 2;
    func_ov027_020ba134((char *)func_ov001_02071248(slot), 1, LoadModeBg1Characters, NULL);
}
