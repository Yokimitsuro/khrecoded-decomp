#include "nitro/types.h"

extern void ScriptCmd_CreateObjectInSlot(void); /* ScriptCmd_CreateObjectInSlot */
extern void func_ov008_020a056c(void); /* ScriptCmd_CreateDelayedGimmick */
extern void func_ov008_020a0650(void); /* ScriptCmd_CreateObjectWithParamInSlot */
extern void func_ov008_020a0688(void); /* ScriptCmd_CreateChildSpawner */

void (*gOv008ScriptObjectCreationHandlers[8])(void) = {
    ScriptCmd_CreateObjectInSlot, /* ScriptCmd_CreateObjectInSlot */
    NULL,
    func_ov008_020a056c, /* ScriptCmd_CreateDelayedGimmick */
    NULL,
    func_ov008_020a0650, /* ScriptCmd_CreateObjectWithParamInSlot */
    NULL,
    func_ov008_020a0688, /* ScriptCmd_CreateChildSpawner */
    NULL,
};
