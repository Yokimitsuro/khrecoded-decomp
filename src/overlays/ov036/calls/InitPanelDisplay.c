#include "nitro/types.h"

typedef u32 (*TexVramAllocFunc)(u32 size, BOOL is4x4, u32 opt);
typedef int (*TexVramFreeFunc)(u32 key);

typedef struct PanelVramWork {
    void *texManagerWork;
    void *scene;
    void *plttManagerWork;
} PanelVramWork;

extern PanelVramWork data_ov036_020c3940;
extern TexVramAllocFunc sDefaultAllocTexVramFunc;
extern TexVramFreeFunc sDefaultFreeTexVramFunc;
extern void GX_SetBankForTex(int tex);
extern void GX_SetBankForTexPltt(int bank);
extern int NNS_GfdGetLnkTexVramManagerWorkSize(int value);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNS_GfdInitLnkTexVramManager(u32 size, u32 base, void *work, u32 workSize, int installCallbacks);
extern int NNS_GfdGetLnkPlttVramManagerWorkSize(int value);
extern void NNS_GfdInitLnkPlttVramManager(u32 size, void *work, u32 workSize, int installCallbacks);
extern void G2x_SetBlendAlpha_(vu16 *reg, int plane1, int plane2, int ev1, int ev2);
extern void G3X_SetClearColor(u32 color, u32 alpha, u32 depth, u32 polygonId, BOOL fog);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);

#define REG_DISP3DCNT (*(vu16 *)0x04000060)
#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)

void InitPanelDisplay(void)
{
    u16 backdropColor = 0;
    u32 workSize;
    u32 key0;
    u32 key1;
    u32 key2;

    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT &= (u16)~0x3004;
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 0x8);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1100;
    GX_SetBankForTex(7);
    GX_SetBankForTexPltt(0x60);
    workSize = NNS_GfdGetLnkTexVramManagerWorkSize(0x60);
    data_ov036_020c3940.texManagerWork = NNSi_FndAllocFromDefaultHeap(workSize);
    NNS_GfdInitLnkTexVramManager(0x60000, 0, data_ov036_020c3940.texManagerWork, workSize, TRUE);
    key0 = sDefaultAllocTexVramFunc(0x20000, FALSE, 0);
    key1 = sDefaultAllocTexVramFunc(0x20000, FALSE, 0);
    key2 = sDefaultAllocTexVramFunc(0x20000, FALSE, 0);
    sDefaultFreeTexVramFunc(key0);
    sDefaultFreeTexVramFunc(key1);
    sDefaultFreeTexVramFunc(key2);
    workSize = NNS_GfdGetLnkPlttVramManagerWorkSize(0x20);
    data_ov036_020c3940.plttManagerWork = NNSi_FndAllocFromDefaultHeap(workSize);
    NNS_GfdInitLnkPlttVramManager(0x8000, data_ov036_020c3940.plttManagerWork, workSize, TRUE);
    REG_DB_BG0CNT = (u16)((REG_DB_BG0CNT & 0x43) | 0x210);
    G2x_SetBlendAlpha_((vu16 *)0x04000050, 1, 0x22, 0, 0x10);
    G3X_SetClearColor(0, 0, 0x7fff, 0x3f, FALSE);
    GX_LoadBGPltt(&backdropColor, 0, sizeof(backdropColor));
}
