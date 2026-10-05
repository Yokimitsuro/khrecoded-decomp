#include "nitro/types.h"

typedef struct TextWindowLayout {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 tileOffset;
    u16 palette;
    u16 unk_0C;
    u16 unk_0E;
} TextWindowLayout;

extern const TextWindowLayout data_ov001_0209dc5c;
extern void *func_ov001_0207123c(void *owner);
extern void *func_ov027_020b9e10(void *widgets, int layer);
extern void InitTextLayerAt(void *window, int bgLayer, void *charBase, void *font, TextWindowLayout *layout);

void InitSceneTextWindow51C(u8 *scene)
{
    TextWindowLayout layout = data_ov001_0209dc5c;

    InitTextLayerAt(scene + 0x51c, 3, func_ov027_020b9e10(func_ov001_0207123c(scene), 0xb), scene + 0x78,
                  &layout);
}
