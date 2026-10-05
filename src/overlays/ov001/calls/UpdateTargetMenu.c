#include "nitro/types.h"

typedef struct TargetMenu {
    u32 flags;
    int state;
} TargetMenu;

extern TargetMenu *data_ov001_020a04a4;
extern void HandleShoulderLockOn(int mode);
extern BOOL func_ov001_0206b06c(void);
extern void SetMenuOpenState(int first, int second);
extern int func_ov021_020af48c(void);
extern u32 func_ov001_02072040(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void SelectNearestTarget(void);

void UpdateTargetMenu(void)
{
    TargetMenu *menu = data_ov001_020a04a4;

    if (menu->flags & 2) {
        HandleShoulderLockOn(0);
        if ((menu->flags & 2) && func_ov001_0206b06c()) {
            SetMenuOpenState(1, 1);
        }
    } else if (!func_ov021_020af48c()) {
        HandleShoulderLockOn(1);
    }
    if (!(menu->flags & 2) && menu->state == 1 && func_ov001_02072040()
        && !func_ov001_020645c8(0x3609) && !func_ov001_020645c8(0x360a)) {
        SelectNearestTarget();
    }
}
