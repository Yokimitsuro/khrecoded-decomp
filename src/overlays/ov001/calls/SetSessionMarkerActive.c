#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x27fc];
    s8 activeMarker;
} Session;

extern Session *data_ov001_020a0480;
extern int func_ov001_02067ed4(void);

void SetSessionMarkerActive(void *object, BOOL enable)
{
    Session *session;

    if (!enable) {
        session = data_ov001_020a0480;
        if (session->activeMarker != -1) {
            session->activeMarker = -1;
        }
    } else {
        session = data_ov001_020a0480;
        if (session->activeMarker == -1) {
            session->activeMarker = func_ov001_02067ed4();
        }
    }
}
