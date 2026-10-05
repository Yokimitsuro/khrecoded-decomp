#include "nitro/types.h"

typedef struct PanelDef {
    u8 pad_00[3];
    u8 itemNumber;
} PanelDef;

typedef struct MenuPanel {
    u8 pad_00[0x1c];
    PanelDef *def;
    u8 column;
    u8 row;
    u16 flags;
} MenuPanel;

typedef struct MenuScene {
    void *table;
    u8 pad_04[8];
    s8 mode;
    s8 selected;
    u8 pad_0E;
    u8 flags;
} MenuScene;

extern MenuScene *data_ov001_020a048c;

extern MenuPanel *func_ov001_02067140(int panelId);
extern void SyncDoorMeshState(MenuPanel *panel, int panelId);
extern void SetPanelItemHighlight(int index, BOOL highlighted);

void ConfigureMenuPanel(int panelId, int flags, int row, int column, BOOL refresh)
{
    MenuPanel *panel = func_ov001_02067140(panelId);

    if (row >= 0) {
        panel->row = row;
    }
    if (column >= 0) {
        panel->column = column;
    }
    if (flags != 0xFFFF) {
        panel->flags = flags;
    }
    if (refresh) {
        SyncDoorMeshState(panel, panelId);
        if (data_ov001_020a048c->flags & 1) {
            SetPanelItemHighlight(panel->def->itemNumber - 1, panel->flags & 2);
        }
    }
}
