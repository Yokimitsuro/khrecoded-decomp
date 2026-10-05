#include "nitro/types.h"

extern void ScriptCmd_CreateObjectInSlot_020a0540(void); /* ScriptCmd_CreateObjectInSlot */
extern void ScriptCmd_CreateObjectAtPosition(void); /* ScriptCmd_CreateObjectAtPosition */
extern void ScriptCmd_SetObjectElementFlag(void); /* ScriptCmd_SetObjectElementFlag */
extern void ScriptCmd_SetObjectElementState(void); /* ScriptCmd_SetObjectElementState */

void (*gOv009ScriptObjectHandlers[7])(void) = {
    ScriptCmd_CreateObjectInSlot_020a0540, /* ScriptCmd_CreateObjectInSlot */
    NULL,
    ScriptCmd_CreateObjectAtPosition, /* ScriptCmd_CreateObjectAtPosition */
    NULL,
    ScriptCmd_SetObjectElementFlag, /* ScriptCmd_SetObjectElementFlag */
    NULL,
    ScriptCmd_SetObjectElementState, /* ScriptCmd_SetObjectElementState */
};
