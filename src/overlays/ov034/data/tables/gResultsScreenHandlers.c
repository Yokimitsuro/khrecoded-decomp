#include "nitro/types.h"

extern void func_ov034_020bdbf0(void); /* StartResultsScreen */
extern void PollResultsScreen(void); /* PollResultsScreen */
extern void func_ov034_020bdc5c(void); /* FinishResultsScreen */
extern void func_ov034_020bdcac(void); /* Gfd_DefaultFreeTexVram */

void (*gResultsScreenHandlers[4])(void) = {
    func_ov034_020bdbf0, /* StartResultsScreen */
    PollResultsScreen, /* PollResultsScreen */
    func_ov034_020bdc5c, /* FinishResultsScreen */
    func_ov034_020bdcac, /* Gfd_DefaultFreeTexVram */
};
