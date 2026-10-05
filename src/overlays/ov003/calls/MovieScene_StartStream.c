#include "nitro/types.h"

typedef struct MovieStreamHeader {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 tile;
    u16 field_a;
    u16 field_c;
    u16 field_e;
    u16 field_10;
    u16 field_12;
    u16 field_14;
} MovieStreamHeader;

typedef struct MovieStreamRequest {
    void *owner;
    void (*callback)(void);
    int flags;
} MovieStreamRequest;

typedef struct MovieStreamScene {
    u16 field_0;
    u16 flags;
    u8 pad_004[0x820];
    u8 streamBuffer[0xc];
    u8 stream[0x84];
    int streamActive;
} MovieStreamScene;

extern MovieStreamScene *data_ov003_020658c0;
extern void MovieScene_UpdateGlobals(void);
extern void openVideoStreamFromHeader(void *stream, int option, void *buffer, MovieStreamHeader *header);
extern u16 *CallIndexedHandler(s32 index);
extern void NNS_G2dMapScrToCharText(u16 *dst, int width, int height, int x, int y, int mapW, int tile, int palette);
extern u32 func_ov003_020649a0(void *stream, int enable);
extern int OpenMoviePlayback(MovieStreamRequest *request);

void MovieScene_StartStream(void *owner)
{
    MovieStreamRequest request;
    MovieStreamHeader header;
    MovieStreamScene *scene = data_ov003_020658c0;

    request.owner = owner;
    request.callback = MovieScene_UpdateGlobals;
    scene->streamActive = 1;
    request.flags = 0;
    header.x = 0;
    header.y = 0;
    header.width = 32;
    header.height = 22;
    header.tile = 1;
    header.field_a = 13;
    header.field_c = 2;
    header.field_e = 0;
    header.field_10 = 0;
    header.field_12 = 0x98;
    header.field_14 = 0;
    openVideoStreamFromHeader(scene->stream, 4, scene->streamBuffer, &header);
    NNS_G2dMapScrToCharText(CallIndexedHandler(5), header.width, header.height, header.x, header.y, 32, header.tile, 14);
    NNS_G2dMapScrToCharText(CallIndexedHandler(6), header.width, header.height, header.x, header.y, 32, header.tile, 14);
    func_ov003_020649a0(scene->stream, 1);
    if (OpenMoviePlayback(&request) == 0) {
        scene->flags |= 2;
    }
}
