#include "nitro/types.h"

extern void func_ov033_020ba604(void); /* BeginResumeMode */
extern void func_ov033_020ba71c(void);
extern void func_ov033_020ba74c(void);
extern void func_ov033_020ba7f0(void);

void (*gResumeModeHandlers[4])(void) = {
    func_ov033_020ba604,
    func_ov033_020ba71c,
    func_ov033_020ba74c,
    func_ov033_020ba7f0,
};
