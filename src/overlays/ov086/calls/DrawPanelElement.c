#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x174];
    u8 screenLayers[0x1c];
} Ov086Menu;

typedef struct {
    u8 pad_00[0x10];
    int layerId;
} PanelElement;

extern Ov086Menu *data_ov086_020c3020;
extern u8 *func_ov039_020bc228(void);
extern void func_ov027_020b9a94(u8 *layers, PanelElement *element);

void DrawPanelElement(PanelElement *element)
{
    int layerId = element->layerId;
    Ov086Menu *menu = data_ov086_020c3020;

    switch (layerId) {
    case 0x19:
    case 0x1a:
        func_ov027_020b9a94(menu->screenLayers, element);
        return;
    }
    func_ov027_020b9a94(func_ov039_020bc228(), element);
}
