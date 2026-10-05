#include "nitro/types.h"

typedef struct ShortLabel {
    char text[7];
} ShortLabel;

extern ShortLabel data_ov001_0209de65[];
extern void func_ov001_02073758(int x, int y, int width, int height, int unk0, int unk1, const char *text);

void DrawShortLabel(int x, int y, int index)
{
    func_ov001_02073758(x, y, 7, 0x6e, 0, 0, data_ov001_0209de65[index].text);
}
