#include "nitro/types.h"

extern void RestoreSavedPlacement(void); /* RestoreSavedPlacement */
extern void EnterPendingRoom(void); /* EnterPendingRoom */
extern void StepSessionScriptState(void); /* StepSessionScriptState */
extern void func_ov001_02061fc0(void); /* LeaveFieldMenu */
extern void SelectNextSessionState(void); /* SelectNextSessionState */
extern void WaitSessionPollAndClearFlags(void); /* WaitSessionPollAndClearFlags */
extern void HandleMenuPromptResult(void); /* HandleMenuPromptResult */
extern void Session_Advance_Or_Lock(void);
extern void StepSessionScriptOrAbort(void); /* StepSessionScriptOrAbort */
extern void func_ov001_02062654(void);
extern void WaitSessionPollCallback(void); /* WaitSessionPollCallback */
extern void func_ov001_0206269c(void); /* HandleSessionScriptResult */
extern void func_ov001_02062838(void); /* ExitSessionAndCommitSave */

void (*gSessionScriptStateHandlers[13])(void) = {
    RestoreSavedPlacement, /* RestoreSavedPlacement */
    EnterPendingRoom, /* EnterPendingRoom */
    StepSessionScriptState, /* StepSessionScriptState */
    func_ov001_02061fc0, /* LeaveFieldMenu */
    SelectNextSessionState, /* SelectNextSessionState */
    WaitSessionPollAndClearFlags, /* WaitSessionPollAndClearFlags */
    HandleMenuPromptResult, /* HandleMenuPromptResult */
    Session_Advance_Or_Lock,
    StepSessionScriptOrAbort, /* StepSessionScriptOrAbort */
    func_ov001_02062654,
    WaitSessionPollCallback, /* WaitSessionPollCallback */
    func_ov001_0206269c, /* HandleSessionScriptResult */
    func_ov001_02062838, /* ExitSessionAndCommitSave */
};
