#include "nitro/types.h"

extern void ScriptCmd_CreateObjectInSlot(void); /* ScriptCmd_CreateObjectInSlot */
extern void ScriptCmd_CreateDelayedGimmick(void); /* ScriptCmd_CreateDelayedGimmick */
extern void ScriptCmd_CreateObjectWithParamInSlot(void); /* ScriptCmd_CreateObjectWithParamInSlot */
extern void ScriptCmd_CreateChildSpawner(void); /* ScriptCmd_CreateChildSpawner */

void (*gOv008ScriptObjectCreationHandlers[8])(void) = {
    ScriptCmd_CreateObjectInSlot, /* ScriptCmd_CreateObjectInSlot */
    NULL,
    ScriptCmd_CreateDelayedGimmick, /* ScriptCmd_CreateDelayedGimmick */
    NULL,
    ScriptCmd_CreateObjectWithParamInSlot, /* ScriptCmd_CreateObjectWithParamInSlot */
    NULL,
    ScriptCmd_CreateChildSpawner, /* ScriptCmd_CreateChildSpawner */
    NULL,
};
