#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
    u8 pad_138[0x4];
    int cursorIndex;
} Ov086Menu;

int GetPageSectionIndex(Ov086Menu *menu)
{
    int section = 0;

    switch (menu->pageIndex) {
    case 0:
        section = 0;
        break;
    case 1:
        section = 1;
        break;
    case 2:
        section = 2;
        break;
    case 3:
        switch (menu->cursorIndex) {
        case 1:
            section = 3;
            break;
        case 2:
            section = 4;
            break;
        case 3:
            section = 5;
            break;
        }
        break;
    case 4:
        section = 6;
        break;
    case 5:
        section = 7;
        break;
    case 6:
        section = 8;
        break;
    case 7:
        break;
    }
    return section;
}
