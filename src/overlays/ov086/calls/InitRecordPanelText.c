#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct {
    int nodeIndices[8];
} GroupNodeTable;

typedef struct {
    u8 messages[0xc];
    u8 statsLayer[0x34];
    u8 menuLayer[0x34];
    u8 titleLayer[0x34];
    void *nodes[26];
    u8 pad110[0x24];
    int group;
    int pad138;
    int subPage;
    u8 pad140[0x34];
    u8 screenLayers[0x1c];
} RecordPanel;

extern const TextFrame data_ov086_020c2128;
extern const GroupNodeTable data_ov086_020c228c;
extern const char sOv086_UiMenuStrLanguageWsbSZ_020c2ff8[];
extern void LoadPackedFileView(RecordPanel *view, const char *path, BOOL fromTail);
extern u16 *func_ov027_020b9e10(u8 *layers, int layerId);
extern void func_ov027_020b9e20(u8 *layers, int layerId);
extern u16 *UpdateScreenWidgetLayer(int layerId);
extern void *func_ov039_020bc9b4(void);
extern void InitTextLayerAt(void *window, int bgLayer, void *charBase, void *font, TextFrame *frame);
extern void *GetWord20(void *window);
extern void *func_02001928(void *window, int selectAsCurrent, int alignFromEnd);
extern void *func_ov027_020ba2c8(RecordPanel *panel, int messageId);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const void *text);
extern void SelectListNodeOrFirst(void *self, void *target);
extern void Text_UploadTileBuffer(void *surface);
extern void DrawRecordPanelStats(RecordPanel *panel);
extern void func_ov086_020bfba0(RecordPanel *panel);
extern void DrawCounterGoalText(RecordPanel *panel);
extern void DrawSecondCounterText(RecordPanel *panel);

void InitRecordPanelText(RecordPanel *panel)
{
    TextFrame frame = data_ov086_020c2128;
    GroupNodeTable table;
    u16 *screen;
    int i;
    int group;
    int first;
    int nodeIndex;
    int sub;

    i = 0;
    LoadPackedFileView(panel, sOv086_UiMenuStrLanguageWsbSZ_020c2ff8, FALSE);
    InitTextLayerAt(panel->statsLayer, 5, func_ov027_020b9e10(panel->screenLayers, 0x19), func_ov039_020bc9b4(), &frame);
    func_ov027_020b9e20(panel->screenLayers, 0x19);
    screen = UpdateScreenWidgetLayer(0x18);
    frame.x = 1;
    frame.y = 0;
    frame.charBase = 1;
    frame.width = 0xb;
    frame.height = 2;
    InitTextLayerAt(panel->menuLayer, 4, screen, func_ov039_020bc9b4(), &frame);
    panel->nodes[19] = GetWord20(panel->menuLayer);
    DrawTextAnchored(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2c8(panel, 10));
    panel->nodes[20] = func_02001928(panel->menuLayer, 1, 0);
    DrawTextAnchored(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2c8(panel, 9));
    for (; i < 3; i++) {
        panel->nodes[21 + i] = func_02001928(panel->menuLayer, 1, 0);
        DrawTextAnchored(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2c8(panel, i + 0xb));
    }
    panel->nodes[24] = func_02001928(panel->menuLayer, 1, 0);
    DrawTextAnchored(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2c8(panel, 0x18));
    panel->nodes[25] = func_02001928(panel->menuLayer, 1, 0);
    DrawTextAnchored(panel->menuLayer, 0, 5, 2, 0x209, func_ov027_020ba2c8(panel, 0x19));
    frame.x = 0xc;
    frame.y = 0x13;
    frame.width = 0x13;
    frame.height = 5;
    frame.charBase += 0x16;
    InitTextLayerAt(panel->titleLayer, 4, screen, func_ov039_020bc9b4(), &frame);
    DrawTextAnchored(panel->titleLayer, 0, 0, 2, 0x209, func_ov027_020ba2c8(panel, 0));
    table = data_ov086_020c228c;
    first = table.nodeIndices[0];
    panel->nodes[first] = GetWord20(panel->statsLayer);
    DrawRecordPanelStats(panel);
    for (group = 1; group < 8; group++) {
        panel->group = group;
        panel->nodes[table.nodeIndices[group]] = func_02001928(panel->statsLayer, 1, 0);
        DrawRecordPanelStats(panel);
    }
    for (group = 0; group < 8; group++) {
        panel->group = group;
        panel->subPage = 1;
        nodeIndex = table.nodeIndices[group];
        panel->nodes[nodeIndex + 1] = func_02001928(panel->statsLayer, 1, 0);
        if (group == 7) {
            DrawSecondCounterText(panel);
        } else {
            func_ov086_020bfba0(panel);
            if (group == 3) {
                for (sub = 2; sub < 4; sub++) {
                    panel->subPage = sub;
                    panel->nodes[nodeIndex + sub] = func_02001928(panel->statsLayer, 1, 0);
                    func_ov086_020bfba0(panel);
                }
            } else if (group == 6) {
                func_ov086_020bfba0(panel);
                panel->subPage = 2;
                panel->nodes[16] = func_02001928(panel->statsLayer, 1, 0);
                DrawCounterGoalText(panel);
            }
        }
    }
    panel->group = 0;
    panel->subPage = 0;
    SelectListNodeOrFirst(panel->statsLayer, panel->nodes[first]);
    Text_UploadTileBuffer(panel->menuLayer);
}
