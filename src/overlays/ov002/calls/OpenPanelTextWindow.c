#include "nitro/types.h"

typedef struct PanelResources {
    u8 pad_00[0x30];
    u8 fontA[0xc];
    u8 fontB[0xc];
} PanelResources;

extern PanelResources *data_ov002_0206c460;
extern void func_ov002_02062470(void *font);
extern void func_ov002_02062504(void *font);

void OpenPanelTextWindow(int window, int font)
{
    switch (window) {
    case 0:
        switch (font) {
        case 0:
            func_ov002_02062470(data_ov002_0206c460->fontA);
            break;
        case 1:
            func_ov002_02062470(data_ov002_0206c460->fontB);
            break;
        }
        break;
    case 1:
        switch (font) {
        case 0:
            func_ov002_02062504(data_ov002_0206c460->fontA);
            break;
        case 1:
            func_ov002_02062504(data_ov002_0206c460->fontB);
            break;
        }
        break;
    }
}
