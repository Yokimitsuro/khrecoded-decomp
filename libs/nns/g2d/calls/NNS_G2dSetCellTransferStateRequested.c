typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000




typedef enum NNS_G2D_VRAM_TYPE {
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB  = 2,
    NNS_G2D_VRAM_TYPE_2DBOTH = 3,
    NNS_G2D_VRAM_TYPE_MAX    = 3
} NNS_G2D_VRAM_TYPE;
typedef struct NNSG2dVRamLocation {
    u32 baseAddrOfVram[NNS_G2D_VRAM_TYPE_MAX];
} NNSG2dVRamLocation;
typedef struct NNSG2dCellTransferState {
    NNSG2dVRamLocation dstVramLocation;
    u32 szDst;
    const void * pSrcNCGR;
    const void * pSrcNCBR;
    u32 szSrcData;
    BOOL bActive;
    u32 bDrawn;
    u32 bTransferRequested;
    u32 srcOffset;
    u32 szByte;
} NNSG2dCellTransferState;
NNSG2dCellTransferState * NNSi_G2dGetCellTransferState(u32 handle);
extern NNSG2dCellTransferState * NNSi_G2dGetCellTransferState (u32 handle);

void NNS_G2dSetCellTransferStateRequested (u32 handle, u32 srcOffset, u32 szByte)
{

    {
        NNSG2dCellTransferState * pState = NNSi_G2dGetCellTransferState(handle);


        pState->bTransferRequested = 0xFFFFFFFF;
        pState->srcOffset = srcOffset;
        pState->szByte = szByte;
    }
}
