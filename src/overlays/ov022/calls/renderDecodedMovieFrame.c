typedef unsigned int u32;
enum MovieContextWord {
    MOVIE_CONTEXT_FRAME_WIDTH = 4,
    MOVIE_CONTEXT_FRAME_HEIGHT = 5,
    MOVIE_CONTEXT_PLANE_TABLE_A = 0x17,
    MOVIE_CONTEXT_PLANE_TABLE_B = 0x18,
    MOVIE_CONTEXT_PLANE_TABLE_C = 0x19,
    MOVIE_CONTEXT_WORKING_PLANE_A = 0x1a,
    MOVIE_CONTEXT_WORKING_PLANE_B = 0x1b,
    MOVIE_CONTEXT_CONSUMED_FRAME_COUNT = 0x27,
    MOVIE_CONTEXT_FRAME_RING_CAPACITY = 0x2a,
    MOVIE_CONTEXT_FRAME_RING_CURSOR = 0x31,
    MOVIE_CONTEXT_CONVERSION_LUMA_SOURCE = 0x0f,
    MOVIE_CONTEXT_CONVERSION_CHROMA_SOURCE = 0x10,
    MOVIE_CONTEXT_CONVERSION_OUTPUT = 0x11,
    MOVIE_CONTEXT_CONVERSION_SOURCE_LINE = 0x12
};
struct MoviePlaneRenderRequest {
    u32 firstPlaneAddress;
    u32 secondPlaneAddress;
    u32 firstWorkingBufferAddress;
    u32 secondWorkingBufferAddress;
    u32 frameWidth;
    u32 frameHeight;
    u32 auxiliaryPlaneAddress;
    u32 pixelClampTableAddress;
    u32 modeIsNotTwo;
};
extern int func_ov022_020a7a1c(int size);
extern int func_ov022_020aaa78(void);
extern void func_ov022_020b715c(struct MoviePlaneRenderRequest *info);
extern void func_ov022_020aa300(u32 *args);
int renderDecodedMovieFrame(int movieContext, int outputBuffer, int sourceLine, int renderMode)
{
    int buffer;
    struct MoviePlaneRenderRequest renderRequest;
    u32 *context = (u32 *)movieContext;
    if (*(u32 *)(movieContext + 0x9c) >= *(u32 *)(movieContext + 0xa0)) return 0;
    if (renderMode != 0) {
        if (context[MOVIE_CONTEXT_WORKING_PLANE_A] == 0) {
            buffer = func_ov022_020a7a1c(context[MOVIE_CONTEXT_FRAME_HEIGHT] << 8);
            context[MOVIE_CONTEXT_WORKING_PLANE_A] = buffer;
            if (buffer == 0) return 0;
        }
        if (context[MOVIE_CONTEXT_WORKING_PLANE_B] == 0) {
            buffer = func_ov022_020a7a1c((context[MOVIE_CONTEXT_FRAME_HEIGHT] >> 1) << 8);
            context[MOVIE_CONTEXT_WORKING_PLANE_B] = buffer;
            if (buffer == 0) return 0;
        }
        renderRequest.firstPlaneAddress = *(u32 *)(context[MOVIE_CONTEXT_PLANE_TABLE_A] + context[MOVIE_CONTEXT_FRAME_RING_CURSOR] * 4);
        renderRequest.secondPlaneAddress = *(u32 *)(context[MOVIE_CONTEXT_PLANE_TABLE_B] + context[MOVIE_CONTEXT_FRAME_RING_CURSOR] * 4);
        renderRequest.firstWorkingBufferAddress = context[MOVIE_CONTEXT_WORKING_PLANE_A];
        renderRequest.secondWorkingBufferAddress = context[MOVIE_CONTEXT_WORKING_PLANE_B];
        renderRequest.frameWidth = context[MOVIE_CONTEXT_FRAME_WIDTH];
        renderRequest.frameHeight = context[MOVIE_CONTEXT_FRAME_HEIGHT];
        renderRequest.auxiliaryPlaneAddress = *(u32 *)(context[MOVIE_CONTEXT_PLANE_TABLE_C] + context[MOVIE_CONTEXT_FRAME_RING_CURSOR] * 4);
        renderRequest.pixelClampTableAddress = (u32)func_ov022_020aaa78();
        if (renderMode == 2) {
            renderRequest.modeIsNotTwo = 0;
        } else {
            renderRequest.modeIsNotTwo = 1;
        }
        func_ov022_020b715c(&renderRequest);
        context[MOVIE_CONTEXT_CONVERSION_LUMA_SOURCE] = context[MOVIE_CONTEXT_WORKING_PLANE_A];
        context[MOVIE_CONTEXT_CONVERSION_CHROMA_SOURCE] = context[MOVIE_CONTEXT_WORKING_PLANE_B];
    } else {
        context[MOVIE_CONTEXT_CONVERSION_LUMA_SOURCE] = *(u32 *)(context[MOVIE_CONTEXT_PLANE_TABLE_A] + context[MOVIE_CONTEXT_FRAME_RING_CURSOR] * 4);
        context[MOVIE_CONTEXT_CONVERSION_CHROMA_SOURCE] = *(u32 *)(context[MOVIE_CONTEXT_PLANE_TABLE_B] + context[MOVIE_CONTEXT_FRAME_RING_CURSOR] * 4);
    }
    context[MOVIE_CONTEXT_CONVERSION_OUTPUT] = (u32)outputBuffer;
    context[MOVIE_CONTEXT_CONVERSION_SOURCE_LINE] = sourceLine << 1;
    func_ov022_020aa300(context + MOVIE_CONTEXT_CONVERSION_LUMA_SOURCE);
    context[MOVIE_CONTEXT_CONSUMED_FRAME_COUNT]++;
    buffer = context[MOVIE_CONTEXT_FRAME_RING_CURSOR] + 1;
    context[MOVIE_CONTEXT_FRAME_RING_CURSOR] = buffer;
    if (buffer == context[MOVIE_CONTEXT_FRAME_RING_CAPACITY]) context[MOVIE_CONTEXT_FRAME_RING_CURSOR] = 0;
    return 1;
}
