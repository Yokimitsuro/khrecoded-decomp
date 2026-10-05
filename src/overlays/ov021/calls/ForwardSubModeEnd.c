#include "nitro/types.h"

extern int *data_ov021_020b56c0;

extern void Camera_SetFlag18IfStandard(void *arg);

void ForwardSubModeEnd(void *arg) {
    switch (*data_ov021_020b56c0) {
    case 0:
        Camera_SetFlag18IfStandard(arg);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
