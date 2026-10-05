#include "nitro/types.h"

extern int *data_ov021_020b56c0;

extern void Camera_RefreshHeading(void);

void ForwardSubModeStart(void) {
    switch (*data_ov021_020b56c0) {
    case 0:
        Camera_RefreshHeading();
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
