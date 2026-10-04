typedef unsigned char u8;
typedef unsigned int u32;

typedef struct NNSiG2dCharCanvasVTable NNSiG2dCharCanvasVTable;
typedef struct NNSG2dCharCanvas {
    u8 *charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    const NNSiG2dCharCanvasVTable *vtable;
} NNSG2dCharCanvas;

extern void MIi_CpuClearFast(u32 data, void *destp, u32 size);

static inline void MI_CpuFillFast(void *dest, u32 data, u32 size)
{
    MIi_CpuClearFast(data, dest, size);
}

static inline int GetCharacterSize(const NNSG2dCharCanvas *pCC)
{
    return 8 * 8 * pCC->dstBpp / 8;
}

static inline u32 SpreadColor32(const NNSG2dCharCanvas *pCC, int cl)
{
    u32 val = (u32)cl;
    if (pCC->dstBpp == 4) {
        val = (val << 4) | val;
        val |= val << 8;
        val |= val << 16;
    } else {
        val = (val << 8) | val;
        val |= val << 16;
    }
    return val;
}

void ClearLine(const NNSG2dCharCanvas *pCC, int cl)
{
    u32 data = SpreadColor32(pCC, cl);
    const int charSize = GetCharacterSize(pCC);
    const int lineSize = charSize * pCC->param;
    const u32 blockSize = charSize * pCC->areaWidth;
    int y;
    u8 *pChar = pCC->charBase;

    for (y = 0; y < pCC->areaHeight; y++) {
        MI_CpuFillFast(pChar, data, blockSize);
        pChar += lineSize;
    }
}
