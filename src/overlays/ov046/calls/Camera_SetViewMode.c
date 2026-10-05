#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
    u8 pad_84[0x138 - 0x84];
    void *controller;
    u8 controllerData[4];
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern int data_ov046_020c33c0[];
extern void func_02029fac(int layer, int id);
extern void func_02029f8c(int layer, int id);
extern void *func_ov047_020c70f8(void *data, CameraManager *camera, void *view);
extern void *InitCameraTarget(void *data, CameraManager *camera, void *view);
extern void *InitCameraPathState(void *data, CameraManager *camera, void *view);

void Camera_SetViewMode(int mode, void *view)
{
    func_02029fac(0, data_ov046_020c33c0[data_ov046_020c3500->type]);
    func_02029f8c(0, data_ov046_020c33c0[mode]);
    data_ov046_020c3500->type = mode;
    switch (mode) {
    case 0:
        data_ov046_020c3500->controller = func_ov047_020c70f8(data_ov046_020c3500->controllerData, data_ov046_020c3500, view);
        break;
    case 1:
        data_ov046_020c3500->controller = InitCameraTarget(data_ov046_020c3500->controllerData, data_ov046_020c3500, view);
        break;
    case 2:
        break;
    case 3:
        data_ov046_020c3500->controller = InitCameraPathState(data_ov046_020c3500->controllerData, data_ov046_020c3500, view);
        break;
    }
}

