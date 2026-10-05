#include "nitro/types.h"

extern void ScriptCmd_CreateObjectInSlot_020a0540(void); /* ScriptCmd_CreateObjectInSlot */
extern void func_ov009_020a056c(void); /* ScriptCmd_CreateObjectAtPosition */
extern void func_ov009_020a05e0(void); /* ScriptCmd_SetObjectElementFlag */
extern void func_ov009_020a0618(void); /* ScriptCmd_SetObjectElementState */

void (*gOv009ScriptObjectHandlers[7])(void) = {
    ScriptCmd_CreateObjectInSlot_020a0540, /* ScriptCmd_CreateObjectInSlot */
    NULL,
    func_ov009_020a056c, /* ScriptCmd_CreateObjectAtPosition */
    NULL,
    func_ov009_020a05e0, /* ScriptCmd_SetObjectElementFlag */
    NULL,
    func_ov009_020a0618, /* ScriptCmd_SetObjectElementState */
};
