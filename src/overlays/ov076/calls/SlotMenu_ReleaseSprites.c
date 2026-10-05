#include "nitro/types.h"

typedef struct SpriteObject {
    u8 data[0x104];
} SpriteObject;

typedef struct SlotMenu {
    u8 pad_00000[0x11fb8];
    SpriteObject frameSprites[5];
    SpriteObject cellSprites[8][3][6];
    SpriteObject cursorSprites[2];
} SlotMenu;

extern void ReleaseResourceAndDetach(SpriteObject *object);

void SlotMenu_ReleaseSprites(SlotMenu *menu)
{
    int page;
    int row;
    int column;

    ReleaseResourceAndDetach(&menu->frameSprites[0]);
    ReleaseResourceAndDetach(&menu->frameSprites[1]);
    ReleaseResourceAndDetach(&menu->frameSprites[2]);
    ReleaseResourceAndDetach(&menu->cursorSprites[0]);
    ReleaseResourceAndDetach(&menu->cursorSprites[1]);
    ReleaseResourceAndDetach(&menu->frameSprites[3]);
    ReleaseResourceAndDetach(&menu->frameSprites[4]);
    for (page = 0; page < 8; page++) {
        for (row = 0; row < 3; row++) {
            for (column = 0; column < 6; column++) {
                if (column != 0) {
                    ReleaseResourceAndDetach(&menu->cellSprites[page][row][column]);
                }
            }
        }
    }
}
