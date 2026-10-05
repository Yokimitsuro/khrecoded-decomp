#include "nitro/types.h"

typedef struct ModeParams {
    int a;
    int b;
    int c;
    int d;
} ModeParams;

extern void func_ov046_020c0b54(int arg);
extern ModeParams *func_ov042_020bd5b0(void);
extern void CommitCameraProjection(int arg, int c, int d, int a, int b);
extern void CommitCameraWithCache(int arg);
extern void func_ov044_020d00a0(int arg);

extern int *data_ov021_020b56c0;

void DispatchModeUpdate(int arg)
{
    ModeParams *params;

    switch (*data_ov021_020b56c0) {
    case 0:
        func_ov046_020c0b54(arg);
        break;
    case 1:
        params = func_ov042_020bd5b0();
        CommitCameraProjection(arg, params->c, params->d, params->a, params->b);
        break;
    case 2:
        CommitCameraWithCache(arg);
        break;
    case 3:
        func_ov044_020d00a0(arg);
        break;
    }
}
