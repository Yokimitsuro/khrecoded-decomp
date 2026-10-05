#include "nitro/types.h"

typedef struct MenuState {
    u8 kind;
    u8 pad_01[3];
    u32 target;
    u8 pad_08[0xc];
} MenuState;

extern BOOL Actor_AnyAnimSlotBit0Set(void);
extern BOOL func_ov001_020645c8(u32 bitOffset);
extern BOOL ReadActiveMenuState(MenuState *out);
extern int func_ov001_0207f91c(u32 target);
extern BOOL IsBattleModeNotTwo(void);
extern BOOL func_ov001_020642a0(void);
extern void SelectFieldMenuPage(int page);

void RefreshFieldMenuPage(void)
{
    BOOL canOpen;
    int page;
    MenuState state;

    canOpen = FALSE;
    page = -1;
    if (Actor_AnyAnimSlotBit0Set() && !func_ov001_020645c8(0x3520)) {
        canOpen = TRUE;
    }
    if (ReadActiveMenuState(&state)) {
        switch (state.kind) {
        case 0:
        case 4:
            break;
        case 2:
            switch (func_ov001_0207f91c(state.target)) {
            case 0:
                if (canOpen) {
                    page = 0;
                }
                break;
            case 1:
                page = 1;
                break;
            case 2:
                page = 2;
                break;
            }
            break;
        case 1:
        case 3:
            if (canOpen) {
                page = 0;
            }
            break;
        }
    } else if (canOpen) {
        page = 0;
    }
    if (IsBattleModeNotTwo() && !func_ov001_020642a0()) {
        page = 3;
    }
    SelectFieldMenuPage(page);
}
