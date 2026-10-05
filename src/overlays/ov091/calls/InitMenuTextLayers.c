#include "nitro/types.h"

typedef struct {
    u8 data[0xc];
} Font;

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 field_0c;
    u16 lineSpacing;
} TextFrame;

typedef struct {
    u8 pad_00[0x10];
    Font font;
    TextLayer listLayer;
    TextLayer statsLayer;
    TextFrame listFrame;
    TextFrame statsFrame;
    u8 pad_a4[0xc9e8 - 0xa4];
    int messages[3];
} MenuScene;

extern char sOv091_TextFontEu10Nftr_020c2c64[];
extern const char *gReportTopTextPath;
extern int func_0200146c(Font *font, const char *path);
extern void LoadPackedFileView(void *view, const char *path, BOOL fromTail);
extern BOOL InitTextLayerDefault(TextLayer *layer, int bg, Font *font, TextFrame *frame);

void InitMenuTextLayers(MenuScene *scene)
{
    func_0200146c(&scene->font, sOv091_TextFontEu10Nftr_020c2c64);
    LoadPackedFileView(scene->messages, gReportTopTextPath, FALSE);
    scene->listFrame.x = 0x11;
    scene->listFrame.y = 4;
    scene->listFrame.width = 10;
    scene->listFrame.height = 0xc;
    scene->listFrame.charBase = 0x100;
    scene->listFrame.palette = 0xf;
    scene->listFrame.field_0c = 0;
    scene->listFrame.lineSpacing = 6;
    InitTextLayerDefault(&scene->listLayer, 1, &scene->font, &scene->listFrame);
    scene->statsFrame.x = 4;
    scene->statsFrame.y = 1;
    scene->statsFrame.width = 0x16;
    scene->statsFrame.height = 0x14;
    scene->statsFrame.charBase = 0x60;
    scene->statsFrame.palette = 0xf;
    scene->statsFrame.field_0c = 0;
    scene->statsFrame.lineSpacing = 3;
    InitTextLayerDefault(&scene->statsLayer, 5, &scene->font, &scene->statsFrame);
}
