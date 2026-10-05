#include "nitro/types.h"

extern void func_ov018_020a1e00(void); /* ScriptCmd_CreateSlotObject */
extern void func_ov018_020a1e30(void); /* ScriptCmd_CreateGroupObject */

void (*gScriptObjectCreationHandlers[4])(void) = {
    func_ov018_020a1e00,
    NULL,
    func_ov018_020a1e30,
    NULL,
};
