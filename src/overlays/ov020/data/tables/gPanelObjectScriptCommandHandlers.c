#include "nitro/types.h"

extern void func_ov020_020a1e00(void); /* ScriptCmd_CreateSlotObjectKind2 */
extern void func_ov020_020a1e30(void);
extern void func_ov020_020a1ef0(void); /* ScriptCmd_CreateSlotObjectKind1 */
extern void func_ov020_020a1f20(void); /* ScriptCmd_CreatePanelObject */
extern void func_ov020_020a201c(void); /* ScriptCmd_CreateSlotObjectKind3 */
extern void func_ov020_020a204c(void); /* ScriptCmd_SpawnPanelCollider */

void (*gPanelObjectScriptCommandHandlers[11])(void) = {
    func_ov020_020a1e00, /* ScriptCmd_CreateSlotObjectKind2 */
    NULL,
    func_ov020_020a1e30,
    NULL,
    func_ov020_020a1ef0, /* ScriptCmd_CreateSlotObjectKind1 */
    NULL,
    func_ov020_020a1f20, /* ScriptCmd_CreatePanelObject */
    NULL,
    func_ov020_020a201c, /* ScriptCmd_CreateSlotObjectKind3 */
    NULL,
    func_ov020_020a204c, /* ScriptCmd_SpawnPanelCollider */
};
