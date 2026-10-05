#include "nitro/types.h"

extern void func_02035de4(void);
extern void DrawVisibleSceneSlots(void);
extern void RunFlaggedEventCallbacks(void);
extern void func_ov001_020876d4(void);
extern void func_ov021_020af528(u32 a);
extern void DrawSceneGroups(void);

void LeaveState(void)
{
    func_ov021_020af528(1);
    DrawVisibleSceneSlots();
    DrawSceneGroups();
    RunFlaggedEventCallbacks();
    func_02035de4();
    func_ov001_020876d4();
}
