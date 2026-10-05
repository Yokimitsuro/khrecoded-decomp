#include "nitro/types.h"

typedef struct RequestState {
    int mode;
    s16 requestId;
} RequestState;

typedef struct Manager {
    u32 unk_00;
    RequestState state;
} Manager;

extern Manager *data_ov001_020a04a4;
extern void ResetPendingRequest(void);
extern void func_ov001_0206c528(int requestId);

void ResumeOrResetRequest(int resume)
{
    RequestState *state = &data_ov001_020a04a4->state;

    if (state->mode != 1 || resume == 0) {
        ResetPendingRequest();
        return;
    }
    func_ov001_0206c528(state->requestId);
}
