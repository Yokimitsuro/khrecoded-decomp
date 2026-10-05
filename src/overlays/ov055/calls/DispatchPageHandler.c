#include "nitro/types.h"

typedef struct MenuPage {
    u8 pad_00[4];
    int kind;
} MenuPage;

extern int func_ov021_020ae958(MenuPage *page, int arg1, int arg2);
extern int func_ov021_020aefd0(MenuPage *page, int arg1, int arg2);

int DispatchPageHandler(MenuPage *page, int arg1, int arg2)
{
    int result = 0;
    switch (page->kind) {
    case 0:
        result = func_ov021_020ae958(page, arg1, arg2);
        break;
    case 4:
        result = func_ov021_020aefd0(page, arg1, arg2);
        break;
    }
    return result;
}
