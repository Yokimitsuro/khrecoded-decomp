#include "nitro/types.h"

typedef struct MenuState {
    char pad0000[0x64fc];
    int isOpen;
    char pad6500[0x66fe - 0x6500];
    s8 cursor;
} MenuState;

extern MenuState *data_ov024_020b7540;
extern void GenerateRandomLinks(void);
extern void func_ov024_020b5848(void *menu, int value);
extern void func_ov024_020b6bd0(void);

void ResetBoardCursor(void *menu, BOOL refresh)
{
    if (refresh) {
        GenerateRandomLinks();
    }
    func_ov024_020b5848(menu, 0);
    if (data_ov024_020b7540->isOpen) {
        data_ov024_020b7540->cursor = -1;
        func_ov024_020b6bd0();
    }
}
