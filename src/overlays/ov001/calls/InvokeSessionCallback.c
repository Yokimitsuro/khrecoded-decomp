#include "nitro/types.h"

typedef void (*SessionCallback)(void *argument);

typedef struct Session {
    u8 pad_0000[0x282c];
    SessionCallback callback;
} Session;

extern Session *data_ov001_020a0480;

void InvokeSessionCallback(void *argument) {
    if (data_ov001_020a0480->callback != NULL) {
        data_ov001_020a0480->callback(argument);
    }
}
