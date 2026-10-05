#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern void *func_ov047_020c382c(void);
extern void *func_ov048_020c3864(void);
extern void *func_ov049_020c4240(void);
extern void *func_ov050_020c3bbc(void);

void *Camera_GetActiveController(void)
{
    switch (data_ov046_020c3500->type) {
    case 0:
        return func_ov047_020c382c();
    case 1:
        return func_ov048_020c3864();
    case 3:
        return func_ov050_020c3bbc();
    case 2:
        return func_ov049_020c4240();
    }
    return NULL;
}
