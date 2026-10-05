typedef unsigned short u16;
typedef unsigned int u32;

struct Mtx22 {
    int m[4];
};

extern void GX_SetBankForBG(int nBank);
extern void GX_SetBankForOBJ(int nBank);
extern void GX_SetBankForBGExtPltt(int nBank);
extern void GX_SetGraphicsMode(u16 unknownMode0, u32 unknownMode1, int unknownMode2);
extern void InitCaptionOam(int bMainScreen);
extern void MTX_Identity22_(struct Mtx22 *pMtx);
extern void G2x_SetBGyAffine_(volatile void *pReg, const struct Mtx22 *pMtx,
                              int nCentreX, int nCentreY, int nX, int nY);

void movie_video_hardware_setup(void)
{
    struct Mtx22 identityMatrix;

    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    GX_SetGraphicsMode(1, 3, 0);

    {
        volatile u16 *reg_bg0cnt = (volatile u16 *)0x04000008;
        volatile u16 *reg_bg1cnt = (volatile u16 *)0x0400000a;
        volatile u16 *reg_bg2cnt = (volatile u16 *)0x0400000c;
        volatile u16 *reg_bg3cnt = (volatile u16 *)0x0400000e;

        *reg_bg0cnt = (u16)((*reg_bg0cnt & 0x43) | 0xc00);
        *reg_bg1cnt = (u16)((*reg_bg1cnt & 0x43) | 0xd00);
        *reg_bg2cnt = (u16)((*reg_bg2cnt & 0x43) | 0xe00);
        *reg_bg3cnt = (u16)((*reg_bg3cnt & 0x43) | 0x284 | 0x4000);
    }

    InitCaptionOam(1);
    GX_SetBankForBGExtPltt(0);
    MTX_Identity22_(&identityMatrix);
    G2x_SetBGyAffine_((volatile void *)0x04000030, &identityMatrix, 0, 0, 0, -0x10);

    {
        volatile u32 *reg_dispcnt = (volatile u32 *)0x04000000;
        volatile u32 *reg_bg0ofs = (volatile u32 *)0x04000010;
        volatile u32 *reg_bg1ofs = (volatile u32 *)0x04000014;
        volatile u32 *reg_bg2ofs = (volatile u32 *)0x04000018;
        volatile u16 *reg_bg0cnt = (volatile u16 *)0x04000008;
        volatile u16 *reg_bg1cnt = (volatile u16 *)0x0400000a;
        volatile u16 *reg_bg2cnt = (volatile u16 *)0x0400000c;
        volatile u16 *reg_bg3cnt = (volatile u16 *)0x0400000e;

        *reg_dispcnt = *reg_dispcnt & ~0x1f00;
        *reg_bg0ofs = 0;
        *reg_bg1ofs = 1;
        *reg_bg2ofs = 0x10000;
        *reg_bg0cnt = (u16)(*reg_bg0cnt & ~3);
        *reg_bg1cnt = (u16)((*reg_bg1cnt & ~3) | 1);
        *reg_bg2cnt = (u16)((*reg_bg2cnt & ~3) | 2);
        *reg_bg3cnt = (u16)((*reg_bg3cnt & ~3) | 3);
    }
}
