#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;
struct PMSleepCallbackInfo {
    void (*callback)(void *arg);
    void *arg;
    u32 pad_08;
    PMSleepCallbackInfo *next;
};

typedef struct {
    u32 pad_00;
    u32 pad_04;
    PMSleepCallbackInfo preSleepCallback;
} PxiState;

extern PxiState data_020597fc;
extern void *PXI_Init_02011428(void);
extern void PMi_InsertPreSleepCallbackEx(PMSleepCallbackInfo *info, int priority);

void RegisterPxiPreSleepCallback(void)
{
    data_020597fc.preSleepCallback.callback = (void (*)(void *))PXI_Init_02011428;
    data_020597fc.preSleepCallback.arg = NULL;
    PMi_InsertPreSleepCallbackEx(&data_020597fc.preSleepCallback, 1000);
}
