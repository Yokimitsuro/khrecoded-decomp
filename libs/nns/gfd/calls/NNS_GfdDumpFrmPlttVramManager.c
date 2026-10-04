typedef unsigned int u32;
typedef void (*NNSGfdFrmPlttVramDebugDumpCallBack)(u32, u32, u32, u32);

extern void FrmPlttVramDebugDumpCallBack_(u32, u32, u32, u32);
extern void NNS_GfdDumpFrmPlttVramManagerEx(NNSGfdFrmPlttVramDebugDumpCallBack callback);

void NNS_GfdDumpFrmPlttVramManager(void)
{
    NNS_GfdDumpFrmPlttVramManagerEx(FrmPlttVramDebugDumpCallBack_);
}