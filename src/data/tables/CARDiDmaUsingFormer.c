#include "nitro/types.h"

extern void MIi_CardDmaCopy32(void); /* MIi_CardDmaCopy32 */
extern void MI_StopDma(void); /* MI_StopDma */

void (*const CARDiDmaUsingFormer[2])(void) = {
    MIi_CardDmaCopy32, /* MIi_CardDmaCopy32 */
    MI_StopDma, /* MI_StopDma */
};
