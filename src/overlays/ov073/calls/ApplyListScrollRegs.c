#include "nitro/types.h"

typedef struct ListView {
    u8 pad_000[0x178];
    BOOL rootDirty;
    BOOL applying;
} ListView;

extern ListView *data_ov073_020c4260;
extern int GetListBgHOffset(ListView *list);
extern void *func_ov039_020bc1ec(void);
extern void UpdateWidgetRootAndFireAlarm(void *root, int keys);

void ApplyListScrollRegs(void)
{
    int offset = GetListBgHOffset(data_ov073_020c4260);
    void *root = func_ov039_020bc1ec();

    if (data_ov073_020c4260->applying == 0) {
        data_ov073_020c4260->applying = 1;
        offset &= 0x1ff;
        *(vu32 *)0x04001018 = offset;
        *(vu32 *)0x0400101c = offset;
        if (data_ov073_020c4260->rootDirty) {
            UpdateWidgetRootAndFireAlarm(root, 0);
            data_ov073_020c4260->rootDirty = FALSE;
        }
        data_ov073_020c4260->applying = 0;
    }
}
