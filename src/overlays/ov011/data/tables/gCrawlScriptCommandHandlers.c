#include "nitro/types.h"

extern void func_ov011_020a0540(void); /* ScriptCmd_ShuffleEntryPositions */
extern void ScriptCmd_SpawnActorInSlot(void); /* ScriptCmd_SpawnActorInSlot */
extern void ScriptCmd_SpawnFieldObject_020a05ac(void); /* ScriptCmd_SpawnFieldObject */
extern void func_ov011_020a0690(void); /* ClearFixedSlots */
extern void func_ov011_020a06c4(void); /* ScriptCmd_PostCrawlScoreLine */
extern void ScriptCmd_PostRequestAndSetPanel(void); /* ScriptCmd_PostRequestAndSetPanel */

void (*gCrawlScriptCommandHandlers[11])(void) = {
    func_ov011_020a0540, /* ScriptCmd_ShuffleEntryPositions */
    NULL,
    ScriptCmd_SpawnActorInSlot, /* ScriptCmd_SpawnActorInSlot */
    NULL,
    ScriptCmd_SpawnFieldObject_020a05ac, /* ScriptCmd_SpawnFieldObject */
    NULL,
    func_ov011_020a0690, /* ClearFixedSlots */
    NULL,
    func_ov011_020a06c4, /* ScriptCmd_PostCrawlScoreLine */
    NULL,
    ScriptCmd_PostRequestAndSetPanel, /* ScriptCmd_PostRequestAndSetPanel */
};
