#include "nitro/types.h"

extern void DefaultStepDone(void);

void (*gDefaultStepHandler[1])(void) = {
    DefaultStepDone,
};
