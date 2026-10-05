#include "nitro/types.h"

extern void func_ov007_020a0540(void); /* ScriptCmd_CreateEntryObjectInSlot */
extern void func_ov007_020a059c(void); /* ScriptCmd_ShowActorEmote */
extern void func_ov007_020a05d8(void); /* ScriptCmd_SetActorWander */
extern void func_ov007_020a0670(void); /* ScriptCmd_EnterPhase */
extern void func_ov007_020a0680(void);
extern void func_ov007_020a06b0(void); /* ScriptCmd_ForceRequest */
extern void func_ov007_020a06d4(void); /* ScriptCmd_PlayValueSequence */
extern void func_ov007_020a0734(void); /* ScriptCmd_SetActorPath */
extern void func_ov007_020a07ac(void); /* ScriptCmd_CreateFieldTask */
extern void func_ov007_020a0810(void); /* ScriptCmd_SetActorTarget */
extern void func_ov007_020a0864(void); /* ScriptCmd_ApplyOperandPair */
extern void func_ov007_020a0894(void); /* ScriptCmd_EnterPhase */

void (*gFieldActorScriptCommandHandlers[23])(void) = {
    func_ov007_020a0540, /* ScriptCmd_CreateEntryObjectInSlot */
    NULL,
    func_ov007_020a059c, /* ScriptCmd_ShowActorEmote */
    NULL,
    func_ov007_020a05d8, /* ScriptCmd_SetActorWander */
    NULL,
    func_ov007_020a0670, /* ScriptCmd_EnterPhase */
    NULL,
    func_ov007_020a0680,
    NULL,
    func_ov007_020a06b0, /* ScriptCmd_ForceRequest */
    NULL,
    func_ov007_020a06d4, /* ScriptCmd_PlayValueSequence */
    NULL,
    func_ov007_020a0734, /* ScriptCmd_SetActorPath */
    NULL,
    func_ov007_020a07ac, /* ScriptCmd_CreateFieldTask */
    NULL,
    func_ov007_020a0810, /* ScriptCmd_SetActorTarget */
    NULL,
    func_ov007_020a0864, /* ScriptCmd_ApplyOperandPair */
    NULL,
    func_ov007_020a0894, /* ScriptCmd_EnterPhase */
};
