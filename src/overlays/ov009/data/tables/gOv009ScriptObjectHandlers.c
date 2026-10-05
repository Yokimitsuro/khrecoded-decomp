#include "nitro/types.h"

extern void ScriptCmd_CreateObjectInSlot_020a0540(void); /* ScriptCmd_CreateObjectInSlot */
extern void func_ov009_020a056c(void); /* ScriptCmd_CreateObjectAtPosition */
extern void ScriptCmd_SetObjectElementFlag(void); /* ScriptCmd_SetObjectElementFlag */
extern void ScriptCmd_SetObjectElementState(void); /* ScriptCmd_SetObjectElementState */

void (*gOv009ScriptObjectHandlers[7])(void) = {
    ScriptCmd_CreateObjectInSlot_020a0540, /* ScriptCmd_CreateObjectInSlot */
    NULL,
    func_ov009_020a056c, /* ScriptCmd_CreateObjectAtPosition */
    NULL,
    ScriptCmd_SetObjectElementFlag, /* ScriptCmd_SetObjectElementFlag */
    NULL,
    ScriptCmd_SetObjectElementState, /* ScriptCmd_SetObjectElementState */
};
