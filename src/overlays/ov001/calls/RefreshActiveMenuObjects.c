#include "nitro/types.h"

typedef struct MenuItemInfo {
    u16 unk_00;
    u16 unk_02_0 : 1;
    u16 isWide : 1;
    u16 unk_02_2 : 14;
    u8 pad_04[0x20];
} MenuItemInfo;

typedef struct MenuContext {
    u32 flags;
    u32 kind;
    u16 itemId;
    u8 pad_0a[0x46];
    u8 pairedObjects[0x7c];
    u8 wideObjects[0x148];
    u8 position[8];
} MenuContext;

extern MenuContext *data_ov001_020a04a4;
extern BOOL func_ov001_02087988(u16 itemId, MenuItemInfo *info);
extern void SetupMirroredObjectPair(void *objects, void *pos);
extern void UpdateCornerSpread(void *objects, void *pos);

void RefreshActiveMenuObjects(void)
{
    MenuContext *menu = data_ov001_020a04a4;
    MenuItemInfo info;

    if (menu == NULL || !(menu->flags & 0x10)) {
        return;
    }
    menu->flags &= ~0x10;
    switch (menu->kind) {
    case 0:
        break;
    case 1:
        if (func_ov001_02087988(menu->itemId, &info)) {
            if (!info.isWide) {
                SetupMirroredObjectPair(menu->pairedObjects, menu->position);
                return;
            }
            UpdateCornerSpread(menu->wideObjects, menu->position);
            return;
        }
        break;
    case 2:
    case 3:
        UpdateCornerSpread(menu->wideObjects, menu->position);
        return;
    case 4:
        SetupMirroredObjectPair(menu->pairedObjects, menu->position);
        return;
    }
}
