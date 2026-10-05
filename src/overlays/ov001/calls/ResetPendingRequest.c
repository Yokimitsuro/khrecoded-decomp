#include "nitro/types.h"

typedef struct PendingRequest {
    s32 unk_00;
    s32 handle;
    s32 active;
} PendingRequest;

typedef struct Manager {
    u8 pad_00[0x3c];
    PendingRequest request;
} Manager;

extern Manager *data_ov001_020a04a4;
extern void HideFieldMessageLine(void);

void ResetPendingRequest(void)
{
    PendingRequest *request = &data_ov001_020a04a4->request;

    if (request->active == 1) {
        HideFieldMessageLine();
    }
    request->active = 0;
    request->handle = -1;
}
