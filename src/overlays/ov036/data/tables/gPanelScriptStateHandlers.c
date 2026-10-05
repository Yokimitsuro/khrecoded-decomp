#include "nitro/types.h"

extern void func_ov036_020ba914(void);
extern void func_ov036_020ba948(void);
extern void RunPanelScriptFrame(void); /* RunPanelScriptFrame */
extern void RunPanelSubScriptFrame(void); /* RunPanelSubScriptFrame */
extern void FinishPanelSceneSetup(void);
extern void func_ov036_020bab74(void); /* ShutdownPanelScene */
extern void func_ov036_020bacf0(void);
extern void func_ov036_020bad34(void);

void (*gPanelScriptStateHandlers[8])(void) = {
    func_ov036_020ba914,
    func_ov036_020ba948,
    RunPanelScriptFrame, /* RunPanelScriptFrame */
    RunPanelSubScriptFrame, /* RunPanelSubScriptFrame */
    FinishPanelSceneSetup,
    func_ov036_020bab74, /* ShutdownPanelScene */
    func_ov036_020bacf0,
    func_ov036_020bad34,
};
