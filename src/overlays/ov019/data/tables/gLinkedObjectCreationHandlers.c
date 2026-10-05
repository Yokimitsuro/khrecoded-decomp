#include "nitro/types.h"

extern void ScriptCmd_CreateSlotObjectKind5(void); /* ScriptCmd_CreateSlotObjectKind5 */
extern void ScriptCmd_SpawnLinkedObject(void); /* ScriptCmd_SpawnLinkedObject */

void (*gLinkedObjectCreationHandlers[4])(void) = {
    ScriptCmd_CreateSlotObjectKind5,
    NULL,
    ScriptCmd_SpawnLinkedObject,
    NULL,
};
