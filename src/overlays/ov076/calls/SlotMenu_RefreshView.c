#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x11f18];
    s32 scrollY;
} SlotMenu;

extern void *func_ov039_020bc1dc(void);
extern void func_ov076_020c7504(SlotMenu *menu, int layerMode, s32 scrollY);
extern void UpdateWidgetRootAndFireAlarm(void *session, int mode);
extern void func_ov076_020c7554(SlotMenu *menu, int layerMode);

void SlotMenu_RefreshView(SlotMenu *menu)
{
    void *session = func_ov039_020bc1dc();

    func_ov076_020c7504(menu, 0, menu->scrollY);
    UpdateWidgetRootAndFireAlarm(session, 0);
    func_ov076_020c7554(menu, 0);
}
