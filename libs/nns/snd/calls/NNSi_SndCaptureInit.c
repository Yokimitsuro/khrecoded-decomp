#include "nitro/types.h"

typedef struct NNSSndCaptureState {
    BOOL active;
} NNSSndCaptureState;

extern volatile BOOL data_0205e248;
extern NNSSndCaptureState data_0205e290;

void NNSi_SndCaptureInit(void)
{
    data_0205e248 = FALSE;
    data_0205e290.active = FALSE;
}
