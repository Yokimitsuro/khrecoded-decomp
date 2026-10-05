#include "nitro/types.h"

extern u8 data_ov035_020bc4d8[8];
extern u8 data_ov035_020bc4e0[8];
extern int NNS_GfdRegisterNewVramTransferTask(int type, int destOffset, void *source, int size);

void QueueColorUpload(BOOL useHighColors) {
    u8 *colors = data_ov035_020bc4e0;

    if (!useHighColors) {
        colors = data_ov035_020bc4d8;
    }
    NNS_GfdRegisterNewVramTransferTask(0xf, 0x186, colors, 8);
}
