typedef unsigned int u32;
typedef int BOOL;
typedef u32 NNSGfdPlttKey;

typedef struct NNSGfdFrmPlttVramManager {
    u32 lowAddress;
    u32 highAddress;
    u32 totalSize;
} NNSGfdFrmPlttVramManager;

extern NNSGfdFrmPlttVramManager sFrmPlttVramManager;
extern NNSGfdPlttKey (*sDefaultAllocPlttVramFunc)(u32, BOOL, u32);
extern int (*sDefaultFreePlttVramFunc)(NNSGfdPlttKey);
extern void NNS_GfdResetFrmPlttVramState(void);
extern NNSGfdPlttKey NNS_GfdAllocFrmPlttVram(u32 size, BOOL fourColor, u32 allocationSide);
extern int NNS_GfdFreeFrmPlttVram(NNSGfdPlttKey key);

void NNS_GfdInitFrmPlttVramManager(u32 totalSize, BOOL useAsDefault)
{
    sFrmPlttVramManager.totalSize = totalSize;
    NNS_GfdResetFrmPlttVramState();

    if (useAsDefault) {
        sDefaultAllocPlttVramFunc = NNS_GfdAllocFrmPlttVram;
        sDefaultFreePlttVramFunc = NNS_GfdFreeFrmPlttVram;
    }
}