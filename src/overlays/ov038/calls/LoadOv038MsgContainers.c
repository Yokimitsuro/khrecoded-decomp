#include "nitro/types.h"

typedef struct Ov038Context {
    u32 unk_00;
    void *containers[3];
} Ov038Context;

extern Ov038Context *data_ov038_020bd164;
extern const char *gResultsResourcePaths[];
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

void LoadOv038MsgContainers(void)
{
    Ov038Context *context = data_ov038_020bd164;
    s32 index;

    for (index = 0; index < 3; index++) {
        context->containers[index] = Msg_OpenContainerAndReadHeader(gResultsResourcePaths[index], 0xe, FALSE);
    }
}
