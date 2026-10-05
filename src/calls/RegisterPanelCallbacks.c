#include "nitro/types.h"

typedef int (*PanelCallback)(void *arg);

extern void setDualArrayEntry(int slot, PanelCallback callback, void *arg);
extern int OpenPanel(void *arg);
extern int UpdatePanelPromptInput(void *arg);
extern int ClosePanelAndResume(void *arg);

void RegisterPanelCallbacks(void)
{
    setDualArrayEntry(0, OpenPanel, NULL);
    setDualArrayEntry(1, UpdatePanelPromptInput, NULL);
    setDualArrayEntry(2, ClosePanelAndResume, NULL);
}
