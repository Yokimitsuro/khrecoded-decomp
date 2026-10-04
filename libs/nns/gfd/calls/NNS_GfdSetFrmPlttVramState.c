typedef unsigned int u32;

typedef struct NNSGfdFrmPlttVramManager {
    u32 lowAddress;
    u32 highAddress;
    u32 totalSize;
} NNSGfdFrmPlttVramManager;

extern NNSGfdFrmPlttVramManager sFrmPlttVramManager;

void NNS_GfdSetFrmPlttVramState(const u32 *state)
{
    u32 low = state[0];
    u32 high = state[1];

    sFrmPlttVramManager.lowAddress = low;
    sFrmPlttVramManager.highAddress = high;
}
