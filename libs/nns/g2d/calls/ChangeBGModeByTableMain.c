typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
typedef volatile unsigned int REGType32v;

#define BG_MODE_WARNING 8

typedef enum GXDispMode {
    GX_DISPMODE_OFF = 0,
    GX_DISPMODE_GRAPHICS = 1
} GXDispMode;

typedef enum GXBGMode {
    GX_BGMODE_0 = 0,
    GX_BGMODE_1,
    GX_BGMODE_2,
    GX_BGMODE_3,
    GX_BGMODE_4,
    GX_BGMODE_5,
    GX_BGMODE_6
} GXBGMode;

typedef enum GXBG0As {
    GX_BG0_AS_2D = 0,
    GX_BG0_AS_3D = 1
} GXBG0As;

extern void GX_SetGraphicsMode(GXDispMode displayMode, GXBGMode bgMode, GXBG0As bg0Mode);

static inline BOOL IsBG03D(void)
{
    return (*(REGType32v *)0x04000000 & 0x00000008) != 0;
}

static inline GXBGMode GetBGModeMain(void)
{
    return (GXBGMode)(*(REGType32v *)0x04000000 & 0x00000007);
}

void ChangeBGModeByTableMain(const u8 modeTable[])
{
    GXBGMode mode = (GXBGMode)modeTable[GetBGModeMain()];
    GXBG0As bg0Mode = IsBG03D() ? GX_BG0_AS_3D : GX_BG0_AS_2D;

    if (mode >= BG_MODE_WARNING) {
        mode -= BG_MODE_WARNING;
    }

    GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, mode, bg0Mode);
}
