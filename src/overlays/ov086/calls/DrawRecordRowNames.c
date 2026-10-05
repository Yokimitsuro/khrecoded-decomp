#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xc];
    u8 textLayer[0x128];
    int pageIndex;
    u8 pad_138[4];
    int stepCount;
    u8 pad_140[0x158 - 0x140];
    u16 pageFlags[7];
    u16 stepFlags[8];
} Ov086Menu;

typedef struct {
    s32 id;
} LayoutCell;

typedef struct {
    u8 pad_00[0x40];
    const u16 *name;
} SlotEntry;

extern int GetPageSectionIndex(Ov086Menu *menu);
extern LayoutCell *GetLayoutCell(int row, int column, int offset);
extern SlotEntry *GetRecordSlotPair0Entry(s32 index);
extern void DrawTextAnchored(void *obj, int x, int y, int color, u32 flags, const u16 *text);

void DrawRecordRowNames(Ov086Menu *menu, int row, int unlockedCount)
{
    int i;
    int y = row * 0x48 + 0x12;
    int section = GetPageSectionIndex(menu);

    for (i = 0; i < 3; i++) {
        int color;
        const u16 *name = GetRecordSlotPair0Entry((s16)GetLayoutCell(section, 3 - row, i)->id)->name;
        DrawTextAnchored(menu->textLayer, 0x2f, y + 1, 1, 0x209, name);
        color = 2;
        if (unlockedCount > i) {
            color = 4;
        }
        DrawTextAnchored(menu->textLayer, 0x2e, y, color, 0x209, name);
        if (menu->pageIndex == 3 && menu->stepCount > 1) {
            if (unlockedCount <= i) {
                menu->stepFlags[menu->stepCount - 2] |= (u16)(1 << (i + row * 3));
            }
        } else if (menu->pageIndex != 7 && unlockedCount <= i) {
            menu->pageFlags[menu->pageIndex] |= (u16)(1 << (i + row * 3));
        }
        y += 0x10;
    }
}
