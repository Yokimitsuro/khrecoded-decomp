#include "nitro/types.h"

extern void ScriptCmd_CreateSlotObjectKind4(void); /* ScriptCmd_CreateSlotObjectKind4 */
extern void ScriptCmd_CreateManagerObject(void); /* ScriptCmd_CreateManagerObject */
extern void ScriptCmd_QueueEntryValueMessage(void); /* ScriptCmd_QueueEntryValueMessage */
extern void ScriptCmd_QueueEntryPositionMessage(void); /* ScriptCmd_QueueEntryPositionMessage */
extern void ScriptCmd_QueueEntryRotationMessage(void); /* ScriptCmd_QueueEntryRotationMessage */
extern void ScriptCmd_QueueEntryDirectionMessage(void); /* ScriptCmd_QueueEntryDirectionMessage */
extern void ScriptCmd_QueueEntryPathMessages(void); /* ScriptCmd_QueueEntryPathMessages */
extern void func_ov017_020a2234(void); /* DefaultStepDone */
extern void ScriptCmd_SetEntryFlag(void); /* ScriptCmd_SetEntryFlag */
extern void ScriptCmd_ResetEntry(void); /* ScriptCmd_ResetEntry */
extern void ScriptCmd_QueueEntryMessage(void); /* ScriptCmd_QueueEntryMessage */
extern void ScriptCmd_QueueEntryCommand(void); /* ScriptCmd_QueueEntryCommand */
extern void ScriptCmd_CreateSlotObjectKind8(void); /* ScriptCmd_CreateSlotObjectKind8 */
extern void ScriptCmd_CreateGridObject(void); /* ScriptCmd_CreateGridObject */
extern void ScriptCmd_CreateSlotObjectKind7(void); /* ScriptCmd_CreateSlotObjectKind7 */
extern void ScriptCmd_CreatePoolObject(void); /* ScriptCmd_CreatePoolObject */
extern void ScriptCmd_InitPool0(void); /* ScriptCmd_InitPool0 */
extern void ScriptCmd_InitPool1(void); /* ScriptCmd_InitPool1 */
extern void ScriptCmd_InitPool2(void); /* ScriptCmd_InitPool2 */
extern void ScriptCmd_InitPool3(void); /* ScriptCmd_InitPool3 */
extern void ScriptCmd_InitPool4(void); /* ScriptCmd_InitPool4 */
extern void ScriptCmd_QueueEntryMessageRange(void); /* ScriptCmd_QueueEntryMessageRange */
extern void ScriptCmd_SetManagerValue(void); /* ScriptCmd_SetManagerValue */

void (*gPoolScriptCommandHandlers[46])(void) = {
    ScriptCmd_CreateSlotObjectKind4, /* ScriptCmd_CreateSlotObjectKind4 */
    NULL,
    ScriptCmd_CreateManagerObject, /* ScriptCmd_CreateManagerObject */
    NULL,
    ScriptCmd_QueueEntryValueMessage, /* ScriptCmd_QueueEntryValueMessage */
    NULL,
    ScriptCmd_QueueEntryPositionMessage, /* ScriptCmd_QueueEntryPositionMessage */
    NULL,
    ScriptCmd_QueueEntryRotationMessage, /* ScriptCmd_QueueEntryRotationMessage */
    NULL,
    ScriptCmd_QueueEntryDirectionMessage, /* ScriptCmd_QueueEntryDirectionMessage */
    NULL,
    ScriptCmd_QueueEntryPathMessages, /* ScriptCmd_QueueEntryPathMessages */
    NULL,
    func_ov017_020a2234, /* DefaultStepDone */
    NULL,
    ScriptCmd_SetEntryFlag, /* ScriptCmd_SetEntryFlag */
    NULL,
    ScriptCmd_ResetEntry, /* ScriptCmd_ResetEntry */
    NULL,
    ScriptCmd_QueueEntryMessage, /* ScriptCmd_QueueEntryMessage */
    NULL,
    ScriptCmd_QueueEntryCommand, /* ScriptCmd_QueueEntryCommand */
    NULL,
    ScriptCmd_CreateSlotObjectKind8, /* ScriptCmd_CreateSlotObjectKind8 */
    NULL,
    ScriptCmd_CreateGridObject, /* ScriptCmd_CreateGridObject */
    NULL,
    ScriptCmd_CreateSlotObjectKind7, /* ScriptCmd_CreateSlotObjectKind7 */
    NULL,
    ScriptCmd_CreatePoolObject, /* ScriptCmd_CreatePoolObject */
    NULL,
    ScriptCmd_InitPool0, /* ScriptCmd_InitPool0 */
    NULL,
    ScriptCmd_InitPool1, /* ScriptCmd_InitPool1 */
    NULL,
    ScriptCmd_InitPool2, /* ScriptCmd_InitPool2 */
    NULL,
    ScriptCmd_InitPool3, /* ScriptCmd_InitPool3 */
    NULL,
    ScriptCmd_InitPool4, /* ScriptCmd_InitPool4 */
    NULL,
    ScriptCmd_QueueEntryMessageRange, /* ScriptCmd_QueueEntryMessageRange */
    NULL,
    ScriptCmd_SetManagerValue, /* ScriptCmd_SetManagerValue */
    NULL,
};
