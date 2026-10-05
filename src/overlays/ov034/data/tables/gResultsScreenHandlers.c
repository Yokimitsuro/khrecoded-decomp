#include "nitro/types.h"

extern void StartResultsScreen(void); /* StartResultsScreen */
extern void PollResultsScreen(void); /* PollResultsScreen */
extern void FinishResultsScreen(void); /* FinishResultsScreen */
extern void func_ov034_020bdcac(void); /* Gfd_DefaultFreeTexVram */

void (*gResultsScreenHandlers[4])(void) = {
    StartResultsScreen, /* StartResultsScreen */
    PollResultsScreen, /* PollResultsScreen */
    FinishResultsScreen, /* FinishResultsScreen */
    func_ov034_020bdcac, /* Gfd_DefaultFreeTexVram */
};
