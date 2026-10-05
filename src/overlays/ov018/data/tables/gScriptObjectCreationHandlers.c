#include "nitro/types.h"

extern void ScriptCmd_CreateSlotObject(void); /* ScriptCmd_CreateSlotObject */
extern void func_ov018_020a1e30(void); /* ScriptCmd_CreateGroupObject */

void (*gScriptObjectCreationHandlers[4])(void) = {
    ScriptCmd_CreateSlotObject,
    NULL,
    func_ov018_020a1e30,
    NULL,
};
