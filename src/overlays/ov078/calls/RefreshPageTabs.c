#include "nitro/types.h"

typedef struct PageMenu {
    u8 pad[0x24];
    void *nodes[8];
    u8 pad44[0x5d0 - 0x44];
    int cursor;
    int page;
} PageMenu;

extern void *func_ov039_020bc1dc(void);
extern void func_ov027_020b91e8(void *scene, void *node, int *offset, int flags);
extern BOOL IsGlobalPackedBitSet(int bit);
extern int ReadGlobalPackedBits(int bit, int width);
extern void SetEntrySlotsVisible(void *scene, void *node, BOOL visible);
extern void func_ov027_020b96c0(void *scene, void *node, int mode);

void RefreshPageTabs(PageMenu *menu)
{
    void *scene = func_ov039_020bc1dc();
    int offset[2];
    int cursor;
    int extra;
    int count;
    int i;

    offset[0] = 0;
    offset[1] = menu->page << 16;
    func_ov027_020b91e8(scene, menu->nodes[1], offset, 3);
    cursor = menu->cursor;
    extra = IsGlobalPackedBitSet(cursor + 0xa01);
    count = ReadGlobalPackedBits(cursor * 2 + 0x9f7, 2);
    count = (u32)(extra != 0) + count;
    for (i = 0; i < count; i++) {
        BOOL inactive = TRUE;
        if (i == menu->page) {
            inactive = FALSE;
        }
        u8 *slot = (u8 *)menu + (i + 2) * 4;
        SetEntrySlotsVisible(scene, *(void **)(slot + 0x24), inactive);
        SetEntrySlotsVisible(scene, *(void **)(slot + 0x30), !inactive);
        func_ov027_020b96c0(scene, *(void **)(slot + 0x30), 0);
    }
}
