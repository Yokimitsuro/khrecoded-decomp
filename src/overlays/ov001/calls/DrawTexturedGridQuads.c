#include "nitro/types.h"
#include "nitro/fx_types.h"

#define reg_G3_COLOR      (*(REGType32v *)0x04000480)
#define reg_G3_TEXCOORD   (*(REGType32v *)0x04000488)
#define reg_G3_VTX_16     (*(REGType32v *)0x0400048c)
#define reg_G3_VTX_XY     (*(REGType32v *)0x04000494)
#define reg_G3_BEGIN_VTXS (*(REGType32v *)0x04000500)
#define reg_G3_END_VTXS   (*(REGType32v *)0x04000504)

#define GX_FX16PAIR(a, b) ((u32)(((u32)(u16)(a)) | ((u32)(u16)(b) << 16)))
#define GX_BEGIN_QUADS 1

static inline void G3_Vtx(fx16 x, fx16 y, fx16 z)
{
    reg_G3_VTX_16 = GX_FX16PAIR(x, y);
    reg_G3_VTX_16 = (u32)(u16)z;
}

static inline void G3_VtxXY(fx16 x, fx16 y)
{
    reg_G3_VTX_XY = GX_FX16PAIR(x, y);
}

static inline void G3_TexCoord(fx16 s, fx16 t)
{
    reg_G3_TEXCOORD = GX_FX16PAIR(s, t);
}

extern volatile u16 data_027e0078[];

extern void func_01fff810(void *a, void *b, int c, int d);
extern void func_01fff8b0(void *a, fx32 *width, fx32 *height);
extern void GXi_FlushCommandList(void);

void DrawTexturedGridQuads(void *texture, void *palette, int rows, int cols, int texParamA, int texParamB, BOOL useColors)
{
    fx32 width;
    fx32 height;
    fx32 x1;
    fx32 y1;
    int colorIndex;
    fx32 x0;
    int row;
    fx32 y0;
    int col;

    func_01fff810(texture, palette, texParamA, texParamB);
    func_01fff8b0(texture, &width, &height);
    GXi_FlushCommandList();
    if (!useColors) {
        reg_G3_COLOR = 0x7fff;
    }
    reg_G3_BEGIN_VTXS = GX_BEGIN_QUADS;
    x0 = -(rows << 11);
    x1 = x0 + 0x1000;
    for (row = 0; row < rows; row++) {
        for (col = 0, y0 = 0, y1 = 0x1000; col < cols; col++, y0 = y1, y1 += 0x1000) {
            colorIndex = 0;
            if (useColors) {
                reg_G3_COLOR = data_027e0078[colorIndex++];
            }
            G3_TexCoord(0, 0);
            G3_Vtx(x0, y1, 0);
            if (useColors) {
                reg_G3_COLOR = data_027e0078[colorIndex++];
            }
            G3_TexCoord(0, height >> 8);
            G3_VtxXY(x0, y0);
            if (useColors) {
                reg_G3_COLOR = data_027e0078[colorIndex++];
            }
            G3_TexCoord(width >> 8, height >> 8);
            G3_VtxXY(x1, y0);
            if (useColors) {
                reg_G3_COLOR = data_027e0078[colorIndex++];
            }
            G3_TexCoord(width >> 8, 0);
            G3_VtxXY(x1, y1);
        }
        x0 = x1;
        x1 += 0x1000;
    }
    reg_G3_END_VTXS = 0;
}
