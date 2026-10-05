#include "nitro/types.h"

extern void func_ov001_02093604(void); /* FSi_CloseFileCommand */
extern void func_ov001_02093608(void); /* StartGroupStageScript */
extern void func_ov001_02093688(void); /* UpdateProximityTrigger */
extern void func_ov001_020938a4(void); /* RunLeaderScriptSlotCommand */
extern void func_ov001_020938fc(void); /* WaitStageActorScript */
extern void func_ov001_02093998(void); /* StartStageActorScript */
extern void func_ov001_02093a2c(void); /* FinishStageEventStep */
extern void func_ov001_02093af0(void); /* NotifyActorGroupAndTarget */
extern void func_ov001_02093b08(void); /* AllocateActorSlotOrReportError */
extern void func_ov001_02093b24(void);
extern void RunGateFadeSequence(void); /* RunGateFadeSequence */

void (*gStageScriptStateHandlers[12])(void) = {
    NULL,
    func_ov001_02093604, /* FSi_CloseFileCommand */
    func_ov001_02093608, /* StartGroupStageScript */
    func_ov001_02093688, /* UpdateProximityTrigger */
    func_ov001_020938a4, /* RunLeaderScriptSlotCommand */
    func_ov001_020938fc, /* WaitStageActorScript */
    func_ov001_02093998, /* StartStageActorScript */
    func_ov001_02093a2c, /* FinishStageEventStep */
    func_ov001_02093af0, /* NotifyActorGroupAndTarget */
    func_ov001_02093b08, /* AllocateActorSlotOrReportError */
    func_ov001_02093b24,
    RunGateFadeSequence, /* RunGateFadeSequence */
};
