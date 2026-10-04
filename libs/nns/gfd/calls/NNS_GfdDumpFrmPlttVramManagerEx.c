typedef unsigned int u32;

typedef struct NNSGfdFrmPlttVramManager {
    u32 lowAddress;
    u32 highAddress;
    u32 totalSize;
} NNSGfdFrmPlttVramManager;

typedef void (*NNSGfdFrmPlttVramDebugDumpCallBack)(u32, u32, u32, u32);

extern NNSGfdFrmPlttVramManager sFrmPlttVramManager;

void NNS_GfdDumpFrmPlttVramManagerEx(NNSGfdFrmPlttVramDebugDumpCallBack callback)
{
    callback(sFrmPlttVramManager.lowAddress,
             sFrmPlttVramManager.highAddress,
             sFrmPlttVramManager.highAddress - sFrmPlttVramManager.lowAddress,
             sFrmPlttVramManager.totalSize);
}