#include "nitro/types.h"

extern void func_ov017_020a1e00(void); /* ScriptCmd_CreateSlotObjectKind4 */
extern void func_ov017_020a1e30(void); /* ScriptCmd_CreateManagerObject */
extern void func_ov017_020a1f38(void); /* ScriptCmd_QueueEntryValueMessage */
extern void func_ov017_020a1f88(void); /* ScriptCmd_QueueEntryPositionMessage */
extern void func_ov017_020a2018(void); /* ScriptCmd_QueueEntryRotationMessage */
extern void func_ov017_020a20d0(void); /* ScriptCmd_QueueEntryDirectionMessage */
extern void func_ov017_020a215c(void); /* ScriptCmd_QueueEntryPathMessages */
extern void func_ov017_020a2234(void); /* DefaultStepDone */
extern void func_ov017_020a1efc(void); /* ScriptCmd_SetEntryFlag */
extern void func_ov017_020a2238(void); /* ScriptCmd_ResetEntry */
extern void func_ov017_020a2264(void); /* ScriptCmd_QueueEntryMessage */
extern void func_ov017_020a22a8(void); /* ScriptCmd_QueueEntryCommand */
extern void func_ov017_020a2340(void); /* ScriptCmd_CreateSlotObjectKind8 */
extern void func_ov017_020a2370(void); /* ScriptCmd_CreateGridObject */
extern void func_ov017_020a2430(void); /* ScriptCmd_CreateSlotObjectKind7 */
extern void func_ov017_020a2460(void); /* ScriptCmd_CreatePoolObject */
extern void func_ov017_020a2574(void); /* ScriptCmd_InitPool0 */
extern void func_ov017_020a258c(void); /* ScriptCmd_InitPool1 */
extern void func_ov017_020a25a4(void); /* ScriptCmd_InitPool2 */
extern void func_ov017_020a25bc(void); /* ScriptCmd_InitPool3 */
extern void func_ov017_020a25d4(void); /* ScriptCmd_InitPool4 */
extern void func_ov017_020a25ec(void); /* ScriptCmd_QueueEntryMessageRange */
extern void func_ov017_020a2648(void); /* ScriptCmd_SetManagerValue */

void (*gPoolScriptCommandHandlers[46])(void) = {
    func_ov017_020a1e00, /* ScriptCmd_CreateSlotObjectKind4 */
    NULL,
    func_ov017_020a1e30, /* ScriptCmd_CreateManagerObject */
    NULL,
    func_ov017_020a1f38, /* ScriptCmd_QueueEntryValueMessage */
    NULL,
    func_ov017_020a1f88, /* ScriptCmd_QueueEntryPositionMessage */
    NULL,
    func_ov017_020a2018, /* ScriptCmd_QueueEntryRotationMessage */
    NULL,
    func_ov017_020a20d0, /* ScriptCmd_QueueEntryDirectionMessage */
    NULL,
    func_ov017_020a215c, /* ScriptCmd_QueueEntryPathMessages */
    NULL,
    func_ov017_020a2234, /* DefaultStepDone */
    NULL,
    func_ov017_020a1efc, /* ScriptCmd_SetEntryFlag */
    NULL,
    func_ov017_020a2238, /* ScriptCmd_ResetEntry */
    NULL,
    func_ov017_020a2264, /* ScriptCmd_QueueEntryMessage */
    NULL,
    func_ov017_020a22a8, /* ScriptCmd_QueueEntryCommand */
    NULL,
    func_ov017_020a2340, /* ScriptCmd_CreateSlotObjectKind8 */
    NULL,
    func_ov017_020a2370, /* ScriptCmd_CreateGridObject */
    NULL,
    func_ov017_020a2430, /* ScriptCmd_CreateSlotObjectKind7 */
    NULL,
    func_ov017_020a2460, /* ScriptCmd_CreatePoolObject */
    NULL,
    func_ov017_020a2574, /* ScriptCmd_InitPool0 */
    NULL,
    func_ov017_020a258c, /* ScriptCmd_InitPool1 */
    NULL,
    func_ov017_020a25a4, /* ScriptCmd_InitPool2 */
    NULL,
    func_ov017_020a25bc, /* ScriptCmd_InitPool3 */
    NULL,
    func_ov017_020a25d4, /* ScriptCmd_InitPool4 */
    NULL,
    func_ov017_020a25ec, /* ScriptCmd_QueueEntryMessageRange */
    NULL,
    func_ov017_020a2648, /* ScriptCmd_SetManagerValue */
    NULL,
};
