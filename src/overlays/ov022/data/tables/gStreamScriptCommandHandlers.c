#include "nitro/types.h"

extern void func_ov022_020a796c(void);
extern void func_ov022_020a79d8(void); /* ScriptCmd_EnterPhase */
extern void func_ov022_020a795c(void); /* ScriptCmd_EnterPhase */
extern void func_ov022_020a7978(void);
extern void func_ov022_020a79b0(void);
extern void func_ov022_020a79e8(void); /* MsgQueue_GetHeap */
extern void func_ov022_020a79f4(void); /* thumbStep */
extern void func_ov022_020a7a08(void); /* CmdPrepareStream */

void (*gStreamScriptCommandHandlers[12])(void) = {
    func_ov022_020a796c,
    NULL,
    func_ov022_020a79d8, /* ScriptCmd_EnterPhase */
    NULL,
    func_ov022_020a795c, /* ScriptCmd_EnterPhase */
    NULL,
    func_ov022_020a7978,
    func_ov022_020a79b0,
    func_ov022_020a79e8, /* MsgQueue_GetHeap */
    func_ov022_020a79f4, /* thumbStep */
    func_ov022_020a7a08, /* CmdPrepareStream */
    NULL,
};
