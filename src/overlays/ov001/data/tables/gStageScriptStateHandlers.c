#include "nitro/types.h"

extern void func_ov001_02093604(void); /* FSi_CloseFileCommand */
extern void StartGroupStageScript(void); /* StartGroupStageScript */
extern void UpdateProximityTrigger(void); /* UpdateProximityTrigger */
extern void RunLeaderScriptSlotCommand(void); /* RunLeaderScriptSlotCommand */
extern void WaitStageActorScript(void); /* WaitStageActorScript */
extern void StartStageActorScript(void); /* StartStageActorScript */
extern void FinishStageEventStep(void); /* FinishStageEventStep */
extern void NotifyActorGroupAndTarget(void); /* NotifyActorGroupAndTarget */
extern void AllocateActorSlotOrReportError(void); /* AllocateActorSlotOrReportError */
extern void FinishActorEventStep(void);
extern void RunGateFadeSequence(void); /* RunGateFadeSequence */

void (*gStageScriptStateHandlers[12])(void) = {
    NULL,
    func_ov001_02093604, /* FSi_CloseFileCommand */
    StartGroupStageScript, /* StartGroupStageScript */
    UpdateProximityTrigger, /* UpdateProximityTrigger */
    RunLeaderScriptSlotCommand, /* RunLeaderScriptSlotCommand */
    WaitStageActorScript, /* WaitStageActorScript */
    StartStageActorScript, /* StartStageActorScript */
    FinishStageEventStep, /* FinishStageEventStep */
    NotifyActorGroupAndTarget, /* NotifyActorGroupAndTarget */
    AllocateActorSlotOrReportError, /* AllocateActorSlotOrReportError */
    FinishActorEventStep,
    RunGateFadeSequence, /* RunGateFadeSequence */
};
