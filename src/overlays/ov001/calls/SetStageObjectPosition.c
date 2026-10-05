#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageObjectHandle {
    u8 pad_00[0x1c];
    VecFx32 position;
} StageObjectHandle;

extern int data_ov001_0209f2e8;
extern StageObjectHandle *GetStageObjectHandle(u32 id);

void SetStageObjectPosition(int index, const VecFx32 *position)
{
    StageObjectHandle *handle;

    if (data_ov001_0209f2e8 != -1) {
        handle = GetStageObjectHandle((u16)(index + 1));
        if (handle != NULL) {
            handle->position = *position;
        }
    }
}
