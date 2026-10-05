#include "nitro/types.h"

extern void ScriptCmd_CreateSlotObjectKind2(void); /* ScriptCmd_CreateSlotObjectKind2 */
extern void func_ov020_020a1e30(void);
extern void ScriptCmd_CreateSlotObjectKind1(void); /* ScriptCmd_CreateSlotObjectKind1 */
extern void ScriptCmd_CreatePanelObject(void); /* ScriptCmd_CreatePanelObject */
extern void ScriptCmd_CreateSlotObjectKind3(void); /* ScriptCmd_CreateSlotObjectKind3 */
extern void ScriptCmd_SpawnPanelCollider(void); /* ScriptCmd_SpawnPanelCollider */

void (*gPanelObjectScriptCommandHandlers[11])(void) = {
    ScriptCmd_CreateSlotObjectKind2, /* ScriptCmd_CreateSlotObjectKind2 */
    NULL,
    func_ov020_020a1e30,
    NULL,
    ScriptCmd_CreateSlotObjectKind1, /* ScriptCmd_CreateSlotObjectKind1 */
    NULL,
    ScriptCmd_CreatePanelObject, /* ScriptCmd_CreatePanelObject */
    NULL,
    ScriptCmd_CreateSlotObjectKind3, /* ScriptCmd_CreateSlotObjectKind3 */
    NULL,
    ScriptCmd_SpawnPanelCollider, /* ScriptCmd_SpawnPanelCollider */
};
