#include "nitro/types.h"

typedef struct {
    u32 address[10];
} NNSGfdFrmTexVramState;

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_DB_DISPCNT (*(volatile u32 *)0x04001000)
#define REG_DISP3DCNT (*(volatile u16 *)0x04000060)

extern void GX_SetBankForTex(int tex);
extern void GX_SetBankForTexPltt(int bank);
extern void NNS_GfdInitFrmTexVramManager(u16 numSlot, BOOL useAsDefault);
extern void NNS_GfdSetFrmTexVramState(const NNSGfdFrmTexVramState *state);
extern void NNS_GfdInitFrmPlttVramManager(int mode, int installCallbacks);
extern void G3X_SetClearColor(unsigned color, unsigned alpha, unsigned depth, unsigned polygonId, BOOL fog);

void InitMovieGraphics_020bb3c0(void)
{
    NNSGfdFrmTexVramState vramState;

    GX_SetBankForTex(0xf);
    GX_SetBankForTexPltt(0x60);
    REG_DISP3DCNT = REG_DISP3DCNT & ~(0x3000 | 0x2);
    REG_DISP3DCNT = REG_DISP3DCNT & 0xcffb;
    REG_DISP3DCNT = (REG_DISP3DCNT & ~0x3000) | 0x8;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (0xf << 8);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (0x1f << 8);
    NNS_GfdInitFrmTexVramManager(4, TRUE);
    vramState.address[0] = 0;
    vramState.address[1] = 0x20000;
    vramState.address[2] = 0;
    vramState.address[3] = 0x20000;
    vramState.address[4] = 0;
    vramState.address[5] = 0;
    vramState.address[6] = 0;
    vramState.address[7] = 0x20000;
    vramState.address[8] = 0;
    vramState.address[9] = 0x20000;
    NNS_GfdSetFrmTexVramState(&vramState);
    NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);
    G3X_SetClearColor(0, 0x1f, 0x7fff, 0x3f, FALSE);
}

