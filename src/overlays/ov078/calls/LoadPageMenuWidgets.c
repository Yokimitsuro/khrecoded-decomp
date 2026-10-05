#include "nitro/types.h"

#define ARCHIVE_FILE_ID(handle, index) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct ObjManagerConfig {
    u32 cellFileId;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} ObjManagerConfig;

typedef struct PageMenu {
    void *archive;
    u8 pad_04[0x20];
    void *nodes[11];
} PageMenu;

extern const ObjManagerConfig data_ov078_020c4fb0;

extern void *func_ov039_020bc1dc(void);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void func_ov027_020b8fb8(void *container, u32 fileId, int count);
extern void *func_ov027_020b90c4(void *container, int id);
extern void func_ov027_020b97d8(void *container, void *widget, int mode);
extern void func_ov027_020b9604(void *container, void *widget);
extern void func_ov027_020b96c0(void *container, void *widget, int mode);
extern int ReadGlobalPackedBits(int bit, int width);

void LoadPageMenuWidgets(PageMenu *menu)
{
    void *container = func_ov039_020bc1dc();
    ObjManagerConfig config = data_ov078_020c4fb0;
    void *stars[5];
    int i;
    int cleared;

    config.cellFileId = ARCHIVE_FILE_ID(menu->archive, 1);
    InitObjManagerAndMark(container, &config);
    func_ov027_020b8fb8(container, ARCHIVE_FILE_ID(menu->archive, 2), 0x12);
    menu->nodes[0] = func_ov027_020b90c4(container, 0xe);
    menu->nodes[1] = func_ov027_020b90c4(container, 0);
    menu->nodes[2] = func_ov027_020b90c4(container, 4);
    menu->nodes[3] = func_ov027_020b90c4(container, 5);
    menu->nodes[4] = func_ov027_020b90c4(container, 6);
    menu->nodes[5] = func_ov027_020b90c4(container, 0xf);
    menu->nodes[6] = func_ov027_020b90c4(container, 0x10);
    menu->nodes[7] = func_ov027_020b90c4(container, 0x11);
    menu->nodes[8] = func_ov027_020b90c4(container, 1);
    menu->nodes[9] = func_ov027_020b90c4(container, 2);
    menu->nodes[10] = func_ov027_020b90c4(container, 3);
    for (i = 0; i < 6; i++) {
        func_ov027_020b97d8(container, menu->nodes[i + 2], 3);
    }
    stars[0] = func_ov027_020b90c4(container, 7);
    stars[1] = func_ov027_020b90c4(container, 8);
    stars[2] = func_ov027_020b90c4(container, 9);
    stars[3] = func_ov027_020b90c4(container, 10);
    stars[4] = func_ov027_020b90c4(container, 0xb);
    for (i = 0; i < 5; i++) {
        void *star = stars[i];
        func_ov027_020b9604(container, star);
        func_ov027_020b96c0(container, star, 0);
    }
    cleared = ReadGlobalPackedBits(0xf38, 4);
    if (cleared > 5) {
        cleared = 5;
    }
    switch (cleared) {
    case 5:
        func_ov027_020b96c0(container, stars[4], 1);
    case 4:
        func_ov027_020b96c0(container, stars[3], 1);
    case 3:
        func_ov027_020b96c0(container, stars[2], 1);
    case 2:
        func_ov027_020b96c0(container, stars[1], 1);
    case 1:
        func_ov027_020b96c0(container, stars[0], 1);
        break;
    }
}
