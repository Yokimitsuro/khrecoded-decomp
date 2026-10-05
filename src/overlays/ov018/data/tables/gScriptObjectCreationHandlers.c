#include "nitro/types.h"

extern void ScriptCmd_CreateSlotObject(void); /* ScriptCmd_CreateSlotObject */
extern void ScriptCmd_CreateGroupObject(void); /* ScriptCmd_CreateGroupObject */

void (*gScriptObjectCreationHandlers[4])(void) = {
    ScriptCmd_CreateSlotObject,
    NULL,
    ScriptCmd_CreateGroupObject,
    NULL,
};
