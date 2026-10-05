#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[6];
    u16 flags;
} MovieContext;

extern MovieContext *data_ov035_020bc500;
extern int RunMenuStateMachine(void);
extern void EndOverlay40Phase(void);

int PollOverlay40Phase(void)
{
    int result = RunMenuStateMachine();

    if (result != 0) {
        EndOverlay40Phase();
        if (result == 1) {
            data_ov035_020bc500->flags |= 0x8000;
            return 5;
        }
        data_ov035_020bc500->flags |= 0x8000;
        return 8;
    }
    return -1;
}