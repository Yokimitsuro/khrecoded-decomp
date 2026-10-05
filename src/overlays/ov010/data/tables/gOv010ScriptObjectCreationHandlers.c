#include "nitro/types.h"

extern void ScriptCmd_CreateShapedObjectClass(void); /* ScriptCmd_CreateShapedObjectClass */
extern void ScriptCmd_CreateObjectWithAngle(void); /* ScriptCmd_CreateObjectWithAngle */
extern void ScriptCmd_SpawnObjectIntoSlot(void); /* ScriptCmd_SpawnObjectIntoSlot */
extern void ScriptCmd_CreateObjectAtOrigin(void); /* ScriptCmd_CreateObjectAtOrigin */

void (*gOv010ScriptObjectCreationHandlers[8])(void) = {
    ScriptCmd_CreateShapedObjectClass, /* ScriptCmd_CreateShapedObjectClass */
    NULL,
    ScriptCmd_CreateObjectWithAngle, /* ScriptCmd_CreateObjectWithAngle */
    NULL,
    ScriptCmd_SpawnObjectIntoSlot, /* ScriptCmd_SpawnObjectIntoSlot */
    NULL,
    ScriptCmd_CreateObjectAtOrigin, /* ScriptCmd_CreateObjectAtOrigin */
    NULL,
};
