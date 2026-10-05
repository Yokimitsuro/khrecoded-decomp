#include "nitro/types.h"

extern void func_ov001_02061c6c(void); /* RestoreSavedPlacement */
extern void func_ov001_02061e54(void); /* EnterPendingRoom */
extern void StepSessionScriptState(void); /* StepSessionScriptState */
extern void func_ov001_02061fc0(void); /* LeaveFieldMenu */
extern void func_ov001_02062150(void); /* SelectNextSessionState */
extern void WaitSessionPollAndClearFlags(void); /* WaitSessionPollAndClearFlags */
extern void func_ov001_020623e8(void); /* HandleMenuPromptResult */
extern void Session_Advance_Or_Lock(void);
extern void func_ov001_020625b8(void); /* StepSessionScriptOrAbort */
extern void func_ov001_02062654(void);
extern void WaitSessionPollCallback(void); /* WaitSessionPollCallback */
extern void func_ov001_0206269c(void); /* HandleSessionScriptResult */
extern void func_ov001_02062838(void); /* ExitSessionAndCommitSave */

void (*gSessionScriptStateHandlers[13])(void) = {
    func_ov001_02061c6c, /* RestoreSavedPlacement */
    func_ov001_02061e54, /* EnterPendingRoom */
    StepSessionScriptState, /* StepSessionScriptState */
    func_ov001_02061fc0, /* LeaveFieldMenu */
    func_ov001_02062150, /* SelectNextSessionState */
    WaitSessionPollAndClearFlags, /* WaitSessionPollAndClearFlags */
    func_ov001_020623e8, /* HandleMenuPromptResult */
    Session_Advance_Or_Lock,
    func_ov001_020625b8, /* StepSessionScriptOrAbort */
    func_ov001_02062654,
    WaitSessionPollCallback, /* WaitSessionPollCallback */
    func_ov001_0206269c, /* HandleSessionScriptResult */
    func_ov001_02062838, /* ExitSessionAndCommitSave */
};
