#include "nitro/types.h"

extern void func_ov099_020c17a4(void);
extern void RunViewerIntroMode(void);

void (*const gEnemyReportStateHandlers[2])(void) = {
    func_ov099_020c17a4,
    RunViewerIntroMode,
};
