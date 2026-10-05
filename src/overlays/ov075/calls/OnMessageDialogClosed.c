#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct {
    u8 pad_00000[0x74];
    s32 dialogOpen;
    u8 pad_00078[0x131a4 - 0x78];
    ResourceContainer *layout;
    u8 pad_131a8[0x13e7c - 0x131a8];
    u8 unk_13E7C;
    u8 pad_13e7d[0x13ea0 - 0x13e7d];
    s32 unk_13EA0;
    u8 pad_13ea4[0x174f8 - 0x13ea4];
    s32 pendingAction;
    u8 pad_174fc[0x17518 - 0x174fc];
    s32 unk_17518;
} MatrixMenu;

extern void *data_0205fe0c;
extern void SetLayoutElementVisible(ResourceContainer *layout, s32 elementId, BOOL visible);
extern void SetUnlockableElementsVisible(ResourceContainer *layout, BOOL visible);
extern s32 ShowNextUnlockNotice(MatrixMenu *menu, s32 mode, s32 arg);
extern void CommitOptionChoice(MatrixMenu *menu, BOOL flag);
extern void func_ov075_020c4390(MatrixMenu *menu);
extern void func_ov073_020c2cc4(int state, int parameter);
extern void func_ov073_020c1ed4(void *save, int arg);

void OnMessageDialogClosed(MatrixMenu *menu)
{
    s32 action = menu->pendingAction;
    BOOL flag = FALSE;

    SetLayoutElementVisible(menu->layout, 0x2a, FALSE);
    menu->dialogOpen = ShowNextUnlockNotice(menu, 0, 0);
    if (menu->dialogOpen == 0 && action != 0) {
        switch (action) {
        case 1:
            if (menu->unk_13E7C != 0) {
                break;
            }
            goto resume;
        case 2:
            if (menu->unk_13E7C == 0) {
                flag = TRUE;
            }
            CommitOptionChoice(menu, flag);
            func_ov073_020c2cc4(3, -1);
            func_ov073_020c1ed4(data_0205fe0c, 0);
            ShowNextUnlockNotice(menu, 1, 0);
            break;
        case 3:
            if (menu->unk_13EA0 == 1) {
                break;
            }
            menu->unk_17518 = 1;
        resume:
            func_ov075_020c4390(menu);
            break;
        }
        menu->pendingAction = 0;
    }
    if (menu->dialogOpen == 0 && action != 3) {
        SetUnlockableElementsVisible(menu->layout, TRUE);
    }
}
