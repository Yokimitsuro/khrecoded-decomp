#include "nitro/types.h"

extern void func_ov036_020bf6dc(void);
extern void OpenQueuedTextWindow(void);
extern void LoadTextWindowFrame(void); /* LoadTextWindowFrame */
extern void func_ov036_020bfe38(void);
extern void StepPanelFade(void);
extern void func_ov036_020c0400(void);
extern void UpdateTextWindowTyping(void); /* UpdateTextWindowTyping */
extern void func_ov036_020c0e30(void);
extern void AdvanceTextWindowPage(void); /* AdvanceTextWindowPage */
extern void StepPanelFadeOut(void);
extern void CloseTextWindowEntry(void); /* CloseTextWindowEntry */
extern void func_ov036_020c1308(void);
extern void func_ov036_020c182c(void);
extern void func_ov036_020c1d48(void);

void (*const gTextWindowStateHandlers[14])(void) = {
    func_ov036_020bf6dc,
    OpenQueuedTextWindow,
    LoadTextWindowFrame, /* LoadTextWindowFrame */
    func_ov036_020bfe38,
    StepPanelFade,
    func_ov036_020c0400,
    UpdateTextWindowTyping, /* UpdateTextWindowTyping */
    func_ov036_020c0e30,
    AdvanceTextWindowPage, /* AdvanceTextWindowPage */
    StepPanelFadeOut,
    CloseTextWindowEntry, /* CloseTextWindowEntry */
    func_ov036_020c1308,
    func_ov036_020c182c,
    func_ov036_020c1d48,
};
