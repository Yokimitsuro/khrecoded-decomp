#include "nitro/types.h"

typedef struct ConfigOption {
    u8 count;
    u8 value;
} ConfigOption;

typedef struct ConfigPage {
    u8 rowCount;
    u8 pad_01[7];
    ConfigOption *options[6];
} ConfigPage;

typedef struct ConfigMenu {
    u8 row;
    u8 page;
    u8 pad_02;
    u8 dirty;
    u8 pageChanged;
    u8 pad_05[0x4b];
    ConfigPage pages[3];
} ConfigMenu;

extern void PlaySoundEffect(int bank, int id);

void ConfigMenu_NextValue(ConfigMenu *menu)
{
    ConfigOption *option = menu->pages[menu->page].options[menu->row];

    option->value++;
    if (option->value == option->count) {
        option->value = 0;
    }
    menu->dirty = TRUE;
    PlaySoundEffect(0, 0);
}
