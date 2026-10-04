typedef unsigned int u32;

typedef struct NNSGfdFrmPlttVramManager {
    u32 lowAddress;
    u32 highAddress;
    u32 totalSize;
} NNSGfdFrmPlttVramManager;

typedef struct NNSGfdFrmPlttVramState {
    u32 lowAddress;
    u32 highAddress;
} NNSGfdFrmPlttVramState;

extern NNSGfdFrmPlttVramManager sFrmPlttVramManager;

void NNS_GfdGetFrmPlttVramState(NNSGfdFrmPlttVramState *state)
{
    state->lowAddress = sFrmPlttVramManager.lowAddress;
    state->highAddress = sFrmPlttVramManager.highAddress;
}