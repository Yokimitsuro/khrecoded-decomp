#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u8 pad_08[4];
} TextFrame;

typedef struct {
    u8 pad_00[0x1c];
    TextLayer listLayer;
    TextLayer statsLayer;
    u8 pad_84[0x10];
    TextFrame statsFrame;
    u8 pad_a0[0x1e8 - 0xa0];
    u8 pad_1e8[0xc800];
    int messages[3];
    int values[5];
    u8 pad_ca08[0xcc7c - 0xca08];
    BOOL altLayout;
} MenuScene;

extern const char data_ov091_020c2c7c[];
extern const char data_ov091_020c2c88[];
extern void CallVirtualHandlerSlot1(TextLayer *layer, int color);
extern int GetNestedModeByte(TextLayer *layer);
extern void Text_UploadTileBuffer(TextLayer *layer);
extern void *func_ov027_020ba2c8(int *messages, int index);
extern void DrawShadowedAnchoredText(TextLayer *layer, int x, int y, int color, int anchor, const void *text);
extern int SPrintfUnbounded(char *dst, const char *fmt, ...);

void DrawRecordSummaryText(MenuScene *scene)
{
    int *messages = scene->messages;
    int lineHeight;
    int y;
    int i;
    int x;
    char firstText[20];
    char otherText[20];

    CallVirtualHandlerSlot1(&scene->listLayer, 0);
    y = 4;
    lineHeight = GetNestedModeByte(&scene->listLayer);
    for (i = 0; i < 5; i++) {
        DrawShadowedAnchoredText(&scene->listLayer, 8, y, 1, 0, func_ov027_020ba2c8(messages, i));
        y += lineHeight + 6;
    }
    Text_UploadTileBuffer(&scene->listLayer);

    CallVirtualHandlerSlot1(&scene->statsLayer, 0);
    x = (scene->statsFrame.width * 8) / 2;
    DrawShadowedAnchoredText(&scene->statsLayer, x, 4, 3, 0x10, func_ov027_020ba2c8(messages, 6));
    y = 0x3e;
    lineHeight = GetNestedModeByte(&scene->statsLayer);
    if (scene->altLayout) {
        y = 0x24;
    }
    for (i = 0; i < 5; i++) {
        DrawShadowedAnchoredText(&scene->statsLayer, 0x1c, y, 1, 0, func_ov027_020ba2c8(messages, i));
        if (i == 0) {
            SPrintfUnbounded(firstText, data_ov091_020c2c7c, scene->values[i]);
            DrawShadowedAnchoredText(&scene->statsLayer, 0x94, y, 1, 0x20, firstText);
        } else {
            SPrintfUnbounded(otherText, data_ov091_020c2c88, scene->values[i]);
            DrawShadowedAnchoredText(&scene->statsLayer, 0x94, y, 1, 0x20, otherText);
        }
        y += lineHeight + 4;
    }
    if (scene->altLayout) {
        DrawShadowedAnchoredText(&scene->statsLayer, 0x58, 0x74, 1, 0x10, func_ov027_020ba2c8(messages, 8));
    }
    Text_UploadTileBuffer(&scene->statsLayer);
}
