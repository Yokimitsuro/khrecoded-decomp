#include "nitro/types.h"

typedef struct {
    u8 pad_00000[7];
    u8 textRefreshFrames;
    u8 pad_00008[0x11fac - 8];
    const void *descriptionText;
} MatrixMenu;

void SetDescriptionText(MatrixMenu *menu, const void *text)
{
    menu->descriptionText = text;
    menu->textRefreshFrames = 1;
}
