typedef unsigned int u32;
typedef unsigned char u8;

typedef struct RenderCommandState {
    u8 *stream00;
    u8 pad04[4];
    u32 flags08;
    u8 pad0c[0xe0 - 0x0c];
    u32 scaleE0;
    u32 alternateScaleE4;
} RenderCommandState;

extern void NNS_G3dGeBufferOP_N(u32 command, const void *words, u32 count);

void EmitJointScaleCommand(RenderCommandState *state, int useAlternate)
{
    u32 values[3];

    if ((state->flags08 & 0x100) == 0 &&
        (state->flags08 & 0x200) == 0) {
        if (useAlternate == 0) {
            values[0] = values[1] = values[2] = state->scaleE0;
        } else {
            values[0] = values[1] = values[2] = state->alternateScaleE4;
        }
        NNS_G3dGeBufferOP_N(0x1b, values, 3);
    }
    state->stream00++;
}
