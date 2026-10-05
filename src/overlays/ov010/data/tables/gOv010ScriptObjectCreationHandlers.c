#include "nitro/types.h"

extern void func_ov010_020a0540(void); /* ScriptCmd_CreateShapedObjectClass */
extern void func_ov010_020a05cc(void); /* ScriptCmd_CreateObjectWithAngle */
extern void func_ov010_020a0654(void); /* ScriptCmd_SpawnObjectIntoSlot */
extern void func_ov010_020a0680(void); /* ScriptCmd_CreateObjectAtOrigin */

void (*gOv010ScriptObjectCreationHandlers[8])(void) = {
    func_ov010_020a0540, /* ScriptCmd_CreateShapedObjectClass */
    NULL,
    func_ov010_020a05cc, /* ScriptCmd_CreateObjectWithAngle */
    NULL,
    func_ov010_020a0654, /* ScriptCmd_SpawnObjectIntoSlot */
    NULL,
    func_ov010_020a0680, /* ScriptCmd_CreateObjectAtOrigin */
    NULL,
};
