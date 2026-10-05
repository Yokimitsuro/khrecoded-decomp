#include "nitro/types.h"

typedef struct LevelEntry {
    u8 id;
    u8 pad_01[0xb];
} LevelEntry;

typedef struct LevelTableFile {
    u8 entryCount;
    u8 sectionCount;
    u8 pad_02[2];
    LevelEntry *entries;
    void *data;
    void *sections[1];
} LevelTableFile;

typedef struct LevelTableHolder {
    LevelTableFile *file;
} LevelTableHolder;

extern LevelTableHolder *data_ov001_020a0490;
extern char sOv001_Em_0209eacc[];
extern u8 *func_ov001_020636e4(void);
extern int findSharedResourceByName(void *table, void *name);
extern LevelTableFile *Archive_LoadFile(u32 fileId, u32 flags);
extern int func_ov001_020644b0(void);
extern void BuildUniqueItemPriceList(u16 *ids, int count);
extern void func_ov001_020876d8(LevelTableFile *file);

static inline BOOL IsMode900(void)
{
    if (func_ov001_020644b0() == 900) {
        return TRUE;
    }
    return FALSE;
}

void LoadLevelTableFile(void)
{
    LevelTableHolder *holder = data_ov001_020a0490;
    u8 *container;
    LevelTableFile *file;
    int i;
    int count;
    u16 ids[64];

    container = func_ov001_020636e4();
    file = Archive_LoadFile((findSharedResourceByName(func_ov001_020636e4(), sOv001_Em_0209eacc) & 0x1ff)
                             | ((((u32)container + 0x8000) & 0xfffffc) << 7 | 0x80000000),
                         2);
    holder->file = file;
    file->entries = (LevelEntry *)((u8 *)file->entries + (u32)file);
    file->data = (u8 *)file->data + (u32)file;
    for (i = 0; i < file->sectionCount; i++) {
        file->sections[i] = (u8 *)file + (u32)file->sections[i];
    }
    if (!IsMode900()) {
        file = holder->file;
        count = 0;
        for (i = 0; i < file->entryCount; i++) {
            ids[i] = file->entries[i].id;
            count++;
        }
        BuildUniqueItemPriceList(ids, count);
    }
    if (holder->file->entryCount != 0) {
        func_ov001_020876d8(holder->file);
    }
}
