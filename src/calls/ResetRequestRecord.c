#include "nitro/types.h"

typedef struct RequestRecord {
    u8 pad_00[0x1cc];
    s32 result;
    s32 handleA;
    s32 handleB;
    u8 pending;
} RequestRecord;

int ResetRequestRecord(RequestRecord *req) {
    req->handleB = -1;
    req->handleA = -1;
    req->pending = 0;
    req->result = 0;
    return 3;
}
