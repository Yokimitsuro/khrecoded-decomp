#include "nitro/types.h"

typedef struct SessionRequest {
    s16 resultId;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 exitKind;
    s16 unk_0A;
} SessionRequest;

typedef struct Session {
    u8 pad_000[0x1a];
    u8 sceneKind;
    u8 pad_01b[0x1ed];
    SessionRequest request;
} Session;

typedef struct SceneArgs {
    s16 unk_00;
    s16 unk_02;
    u8 sceneKind;
} SceneArgs;

extern Session *data_ov001_020a0480;

void InitSessionRequestFromArgs(SceneArgs *args) {
    Session *session = data_ov001_020a0480;
    session->sceneKind = args->sceneKind;
    session->request.resultId = -1;
    session->request.unk_02 = -1;
    session->request.unk_0A = -1;
    session->request.unk_04 = args->unk_00;
    session->request.unk_06 = args->unk_02;
}
