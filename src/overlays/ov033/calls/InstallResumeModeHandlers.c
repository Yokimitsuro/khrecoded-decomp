#include "nitro/types.h"

typedef void (*ModeHandler)(void);

typedef struct ModeHandlers {
    ModeHandler handlers[10];
} ModeHandlers;

extern void func_ov033_020ba8f4(void);
extern void func_ov033_020ba918(void);
extern void func_ov033_020ba944(void);
extern void func_ov033_020ba968(void);
extern void func_ov033_020ba98c(void);
extern void func_ov033_020ba9b0(void);
extern void func_ov033_020ba9d0(void);
extern void func_ov033_020ba9d8(void);

void InstallResumeModeHandlers(ModeHandlers *table)
{
    table->handlers[0] = func_ov033_020ba8f4;
    table->handlers[1] = func_ov033_020ba918;
    table->handlers[2] = func_ov033_020ba944;
    table->handlers[3] = func_ov033_020ba968;
    table->handlers[4] = func_ov033_020ba98c;
    table->handlers[5] = func_ov033_020ba9b0;
    table->handlers[6] = NULL;
    table->handlers[7] = func_ov033_020ba9d0;
    table->handlers[8] = NULL;
    table->handlers[9] = func_ov033_020ba9d8;
}
