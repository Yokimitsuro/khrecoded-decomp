#include "nitro/types.h"

extern void Gfd_LoadTex(void); /* func */
extern void Gfd_LoadTexPltt(void); /* func */
extern void GX_LoadBG0Char(void); /* GX_LoadBG0Char */
extern void GX_LoadBG1Char(void); /* GX_LoadBG1Char */
extern void GX_LoadBG2Char(void); /* GX_LoadBG2Char */
extern void GX_LoadBG3Char(void); /* GX_LoadBG3Char */
extern void GX_LoadBG0Scr(void); /* GX_LoadBG0Scr */
extern void GX_LoadBG1Scr(void); /* GX_LoadBG1Scr */
extern void GX_LoadBG2Scr(void); /* GX_LoadBG2Scr */
extern void GX_LoadBG3Scr(void); /* GX_LoadBG3Scr */
extern void GX_LoadOBJPltt(void); /* GX_LoadOBJPltt */
extern void GX_LoadBGPltt(void); /* func */
extern void DoTransfer2dObjExtPlttMain(void); /* func */
extern void DoTransfer2dBGExtPlttMain(void); /* func */
extern void GX_LoadOAM(void); /* func */
extern void GX_LoadOBJ(void); /* func */
extern void GXS_LoadBG0Char(void); /* GXS_LoadBG0Char */
extern void GXS_LoadBG1Char(void); /* GXS_LoadBG1Char */
extern void GXS_LoadBG2Char(void); /* GXS_LoadBG2Char */
extern void GXS_LoadBG3Char(void); /* GXS_LoadBG3Char */
extern void GXS_LoadBG0Scr(void); /* GXS_LoadBG0Scr */
extern void GXS_LoadBG1Scr(void); /* GXS_LoadBG1Scr */
extern void GXS_LoadBG2Scr(void); /* GXS_LoadBG2Scr */
extern void GXS_LoadBG3Scr(void); /* GXS_LoadBG3Scr */
extern void GXS_LoadOBJPltt(void); /* GXS_LoadOBJPltt */
extern void GXS_LoadBGPltt(void); /* GXS_LoadBGPltt */
extern void Gfd_LoadSubObjExtPltt(void); /* func */
extern void Gfd_LoadSubBgExtPltt(void); /* func */
extern void GXS_LoadOAM(void); /* GXS_LoadOAM */
extern void GXS_LoadOBJ(void); /* func */
extern void AllocatorAllocForExpHeap(void);
extern void AllocatorFreeForExpHeap(void);
extern void AllocatorAllocForSDKHeap(void);
extern void AllocatorFreeForSDKHeap(void);

void (*const sVramTransferTaskHandlers[36])(void) = {
    Gfd_LoadTex, /* func */
    Gfd_LoadTexPltt, /* func */
    NULL,
    NULL,
    GX_LoadBG0Char, /* GX_LoadBG0Char */
    GX_LoadBG1Char, /* GX_LoadBG1Char */
    GX_LoadBG2Char, /* GX_LoadBG2Char */
    GX_LoadBG3Char, /* GX_LoadBG3Char */
    GX_LoadBG0Scr, /* GX_LoadBG0Scr */
    GX_LoadBG1Scr, /* GX_LoadBG1Scr */
    GX_LoadBG2Scr, /* GX_LoadBG2Scr */
    GX_LoadBG3Scr, /* GX_LoadBG3Scr */
    NULL,
    NULL,
    GX_LoadOBJPltt, /* GX_LoadOBJPltt */
    GX_LoadBGPltt, /* func */
    DoTransfer2dObjExtPlttMain, /* func */
    DoTransfer2dBGExtPlttMain, /* func */
    GX_LoadOAM, /* func */
    GX_LoadOBJ, /* func */
    GXS_LoadBG0Char, /* GXS_LoadBG0Char */
    GXS_LoadBG1Char, /* GXS_LoadBG1Char */
    GXS_LoadBG2Char, /* GXS_LoadBG2Char */
    GXS_LoadBG3Char, /* GXS_LoadBG3Char */
    GXS_LoadBG0Scr, /* GXS_LoadBG0Scr */
    GXS_LoadBG1Scr, /* GXS_LoadBG1Scr */
    GXS_LoadBG2Scr, /* GXS_LoadBG2Scr */
    GXS_LoadBG3Scr, /* GXS_LoadBG3Scr */
    NULL,
    NULL,
    GXS_LoadOBJPltt, /* GXS_LoadOBJPltt */
    GXS_LoadBGPltt, /* GXS_LoadBGPltt */
    Gfd_LoadSubObjExtPltt, /* func */
    Gfd_LoadSubBgExtPltt, /* func */
    GXS_LoadOAM, /* GXS_LoadOAM */
    GXS_LoadOBJ, /* func */
};

void (*const sAllocatorFuncForExpHeap[2])(void) = {
    AllocatorAllocForExpHeap,
    AllocatorFreeForExpHeap,
};

void (*const sAllocatorFuncForSDKHeap[2])(void) = {
    AllocatorAllocForSDKHeap,
    AllocatorFreeForSDKHeap,
};
