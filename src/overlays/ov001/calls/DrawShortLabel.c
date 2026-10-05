#include "nitro/types.h"

typedef struct ShortLabel {
    char text[7];
} ShortLabel;

extern ShortLabel data_ov001_0209de65[];
extern void BlitNibbleRunPadded(int x, int y, int width, int height, int unk0, int unk1, const char *text);

void DrawShortLabel(int x, int y, int index)
{
    BlitNibbleRunPadded(x, y, 7, 0x6e, 0, 0, data_ov001_0209de65[index].text);
}
