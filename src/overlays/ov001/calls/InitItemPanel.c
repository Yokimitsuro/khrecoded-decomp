#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Panel Panel;

struct Panel {
    u8 pad_00[0x40];
    VecFx32 position;
    u8 pad_4c[0x58 - 0x4c];
    u32 low : 16;
    s32 itemId : 11;
    u32 high : 5;
    int param;
    u8 pad_60[0x74 - 0x60];
    void *widget;
};

extern void func_ov001_0208273c(Panel *panel, int state);
extern void LinkPendingNode(void *widget);

void InitItemPanel(Panel *panel, const VecFx32 *position, int itemId, int param) {
    func_ov001_0208273c(panel, 0);
    panel->position = *position;
    panel->param = param;
    panel->itemId = itemId;
    LinkPendingNode(panel->widget);
}
