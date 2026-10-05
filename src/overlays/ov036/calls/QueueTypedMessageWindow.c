#include "nitro/types.h"

typedef struct WindowSize {
    s32 width;
    s32 height;
} WindowSize;

typedef struct MessageRequest {
    s32 x;
    s32 y;
    WindowSize *size;
    s32 style;
    u16 *text;
    s32 portraitId;
    s32 portraitPose;
    s32 kind;
} MessageRequest;

extern void QueueMessageWindow(MessageRequest *request);

void QueueTypedMessageWindow(MessageRequest *request) {
    switch (request->x) {
    case 1:
    case 14:
    case 15:
        request->kind = 4;
        break;
    default:
        request->kind = 0;
        break;
    }
    QueueMessageWindow(request);
}