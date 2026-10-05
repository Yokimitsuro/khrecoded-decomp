#include "nitro/types.h"

typedef struct MenuContext {
    u32 flags;
} MenuContext;

extern MenuContext *data_ov001_020a04a4;
extern void SetMenuOpenState(int first, int second);
extern void ResetPendingRequest(void);

void SetMenuHighlight(BOOL enable)
{
    MenuContext *menu = data_ov001_020a04a4;

    if (menu != NULL) {
        if (enable) {
            menu->flags |= 4;
        } else {
            menu->flags &= ~4;
        }
        SetMenuOpenState(0, 0);
        ResetPendingRequest();
    }
}
