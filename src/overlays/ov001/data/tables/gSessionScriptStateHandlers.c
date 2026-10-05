#include "nitro/types.h"

extern void func_ov001_02061c6c(void); /* RestoreSavedPlacement */
extern void func_ov001_02061e54(void); /* EnterPendingRoom */
extern void func_ov001_02061f64(void); /* StepSessionScriptState */
extern void func_ov001_02061fc0(void); /* LeaveFieldMenu */
extern void func_ov001_02062150(void); /* SelectNextSessionState */
extern void func_ov001_020623b0(void); /* WaitSessionPollAndClearFlags */
extern void func_ov001_020623e8(void); /* HandleMenuPromptResult */
extern void func_ov001_0206257c(void);
extern void func_ov001_020625b8(void); /* StepSessionScriptOrAbort */
extern void func_ov001_02062654(void);
extern void func_ov001_02062674(void); /* WaitSessionPollCallback */
extern void func_ov001_0206269c(void); /* HandleSessionScriptResult */
extern void func_ov001_02062838(void); /* ExitSessionAndCommitSave */

void (*gSessionScriptStateHandlers[13])(void) = {
    func_ov001_02061c6c, /* RestoreSavedPlacement */
    func_ov001_02061e54, /* EnterPendingRoom */
    func_ov001_02061f64, /* StepSessionScriptState */
    func_ov001_02061fc0, /* LeaveFieldMenu */
    func_ov001_02062150, /* SelectNextSessionState */
    func_ov001_020623b0, /* WaitSessionPollAndClearFlags */
    func_ov001_020623e8, /* HandleMenuPromptResult */
    func_ov001_0206257c,
    func_ov001_020625b8, /* StepSessionScriptOrAbort */
    func_ov001_02062654,
    func_ov001_02062674, /* WaitSessionPollCallback */
    func_ov001_0206269c, /* HandleSessionScriptResult */
    func_ov001_02062838, /* ExitSessionAndCommitSave */
};
