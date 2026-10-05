#include "nitro/types.h"
#include "nitro/fx.h"

#define NNS_G3D_RSFLAG_CURRENT_NODEDESC_VALID 0x10

typedef struct NNSG3dRS {
    u8 pad_00[8];
    u32 flag;
    u8 pad_0c[0xae - 0xc];
    u8 currentNodeDesc;
} NNSG3dRS;

typedef struct NodeMatrixCapture {
    u16 flags;
    u8 pad_02[0x80 - 0x2];
    MtxFx43 matrix;
    u8 pad_b0[0xc4 - 0xb0];
    struct NodeMatrixCapture *next;
    s16 nodeId;
} NodeMatrixCapture;

typedef struct CaptureOwner {
    u8 pad_00[0xc0];
    NodeMatrixCapture *captures;
} CaptureOwner;

extern CaptureOwner *data_0206076c;

extern void NNS_G3dGetCurrentMtx(MtxFx43 *m, void *n);
extern void ApplyQuaternionCorrectionToMatrix(void *mtx);

void CaptureTrackedNodeMatrixCallback(NNSG3dRS *rs)
{
    NodeMatrixCapture *capture;

    for (capture = data_0206076c->captures; capture != NULL; capture = capture->next) {
        if (capture->nodeId == ((rs->flag & NNS_G3D_RSFLAG_CURRENT_NODEDESC_VALID) ? rs->currentNodeDesc : -1)) {
            NNS_G3dGetCurrentMtx(&capture->matrix, NULL);
            if (capture->flags & 8) {
                ApplyQuaternionCorrectionToMatrix(&capture->matrix);
            }
            return;
        }
    }
}
