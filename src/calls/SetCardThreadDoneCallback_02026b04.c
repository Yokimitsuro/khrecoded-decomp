#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    void (*doneCallback)(void);
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void func_020270f4(void);

void SetCardThreadDoneCallback_02026b04(void)
{
    data_0205fe00.doneCallback = func_020270f4;
}
