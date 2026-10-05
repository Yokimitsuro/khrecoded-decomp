#include "nitro/types.h"

extern void ScriptCmd_CreateSlotObjectKind5(void); /* ScriptCmd_CreateSlotObjectKind5 */
extern void func_ov019_020a1e30(void); /* ScriptCmd_SpawnLinkedObject */

void (*gLinkedObjectCreationHandlers[4])(void) = {
    ScriptCmd_CreateSlotObjectKind5,
    NULL,
    func_ov019_020a1e30,
    NULL,
};
