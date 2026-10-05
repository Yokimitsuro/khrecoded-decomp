#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc];
    int entryMode;
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void func_ov002_0206331c(int entryMode);

void RefreshMenuContext(void)
{
    func_ov002_0206331c(data_ov002_0206c460->entryMode);
}
