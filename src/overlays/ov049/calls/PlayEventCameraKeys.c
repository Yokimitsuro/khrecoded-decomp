#include "nitro/types.h"
#include "nitro/fx_types.h"

#define KEY_UNSET 0x7fffffff
#define DEG_TO_ANGLE(deg) ((s32)(((s64)(deg) * 0x3244) / 0xb4000))

typedef struct CameraKeyParams {
    s32 time;
    s32 arg5;
    s32 angle;
    fx32 distance;
    s32 duration;
    s32 arg4;
} CameraKeyParams;

typedef struct CameraKey {
    s32 type;
    s32 time;
    s32 arg5;
    s32 angle;
    fx32 distance;
    s32 duration;
    s32 arg4;
} CameraKey;

typedef struct CameraKeyTrack {
    u8 pad00[0x54];
    CameraKey *keys;
    u16 count;
    u8 pad5a[2];
    s32 time;
} CameraKeyTrack;

typedef struct EventCameraWork {
    u8 pad000[0x18c];
    CameraKeyTrack *track;
} EventCameraWork;

extern void (*gCameraMotionInitializers[])(CameraKeyParams *params);
extern void Camera_StartViewMotionAtAngle(s32 angle, fx32 distance, s32 duration, s32 arg4, s32 arg5);

void PlayEventCameraKeys(EventCameraWork *work)
{
    int i = 0;
    int count = work->track->count;
    CameraKeyParams params;
    s32 value;

    for (; i < count; i++) {
        gCameraMotionInitializers[work->track->keys[i].type](&params);
        params.time = work->track->keys[i].time;
        if (params.time >= work->track->time && params.time < work->track->time + 0x1000) {
            value = work->track->keys[i].arg5;
            if (value != KEY_UNSET) {
                params.arg5 = value;
            }
            value = work->track->keys[i].angle;
            if (value != KEY_UNSET) {
                params.angle = value;
            }
            value = work->track->keys[i].distance;
            if (value != KEY_UNSET) {
                params.distance = value;
            }
            value = work->track->keys[i].duration;
            if (value != KEY_UNSET) {
                params.duration = value;
            }
            value = work->track->keys[i].arg4;
            if (value != KEY_UNSET) {
                params.arg4 = value;
            }
            Camera_StartViewMotionAtAngle(DEG_TO_ANGLE(params.angle), params.distance, params.duration, DEG_TO_ANGLE(params.arg4), params.arg5);
        }
    }
    work->track->time += 0x1000;
}
