typedef unsigned int u32;

typedef struct NNSGfdFrmPlttVramManager {
    u32 lowAddress;
    u32 highAddress;
    u32 totalSize;
} NNSGfdFrmPlttVramManager;

extern NNSGfdFrmPlttVramManager sFrmPlttVramManager;

void NNS_GfdResetFrmPlttVramState(void)
{
    sFrmPlttVramManager.lowAddress = 0;
    sFrmPlttVramManager.highAddress = sFrmPlttVramManager.totalSize;
}