#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_0000[0x69e8];
    u8 panel[1];
} MenuContext;

extern MenuContext *data_ov002_0206c464;
extern void func_ov027_020b90b8(void *panel, void (*callback)(void));
extern void OnPopupElementTouched(void);

void ReleaseMenuPanelCallback(void)
{
    func_ov027_020b90b8(data_ov002_0206c464->panel, OnPopupElementTouched);
}
