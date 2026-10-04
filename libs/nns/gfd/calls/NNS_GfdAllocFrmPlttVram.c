typedef unsigned int u32;
typedef int BOOL;

#define NNS_GFD_PLTTSIZE_MIN 8
#define NNS_GFD_PLTTSIZE_MAX 0x7fff8
#define NNS_GFD_4PLTT_MAX_ADDR 0x10000
#define NNS_GFD_ALLOC_ERROR_PLTTKEY 0
#define NNS_GFD_ALLOC_FROM_LOW 1

typedef u32 NNSGfdPlttKey;

typedef struct NNSGfdFrmPlttVramManager {
    u32 lowAddress;
    u32 highAddress;
    u32 totalSize;
} NNSGfdFrmPlttVramManager;

extern NNSGfdFrmPlttVramManager sFrmPlttVramManager;

static inline u32 RoundupPaletteSize(u32 size)
{
    if (size == 0) {
        return NNS_GFD_PLTTSIZE_MIN;
    }
    return (size + 7) & ~7;
}

static inline NNSGfdPlttKey MakePaletteKey(u32 address, u32 size)
{
    return ((size >> 3) << 16) | (0xffff & (address >> 3));
}

static inline u32 GetUpperAlignment(u32 address, BOOL fourColor)
{
    if (fourColor) {
        return 7 & (8 - (address & 7));
    }
    return 0xf & (0x10 - (address & 0xf));
}

static inline u32 GetLowerAlignment(u32 address, BOOL fourColor)
{
    if (fourColor) {
        return address & 7;
    }
    return address & 0xf;
}

static inline u32 GetPaletteCapacity(void)
{
    return sFrmPlttVramManager.highAddress - sFrmPlttVramManager.lowAddress;
}

static inline BOOL AllocatePaletteLow(
    u32 size,
    BOOL fourColor,
    u32 *resultAddress
)
{
    u32 address = sFrmPlttVramManager.lowAddress;
    u32 alignment = GetUpperAlignment(address, fourColor);
    u32 increase = size + alignment;

    if (GetPaletteCapacity() >= increase) {
        u32 tail = sFrmPlttVramManager.lowAddress + increase;

        if (fourColor && tail > NNS_GFD_4PLTT_MAX_ADDR) {
            return 0;
        }

        *resultAddress = sFrmPlttVramManager.lowAddress + alignment;
        sFrmPlttVramManager.lowAddress += increase;
        return 1;
    }
    return 0;
}

static inline BOOL AllocatePaletteHigh(
    u32 size,
    BOOL fourColor,
    u32 *resultAddress
)
{
    if (sFrmPlttVramManager.highAddress >= size) {
        u32 address = sFrmPlttVramManager.highAddress - size;
        u32 alignment = GetLowerAlignment(address, fourColor);
        u32 increase = size + alignment;

        if (GetPaletteCapacity() >= increase) {
            u32 tail = sFrmPlttVramManager.highAddress;

            if (fourColor && tail > NNS_GFD_4PLTT_MAX_ADDR) {
                return 0;
            }

            sFrmPlttVramManager.highAddress -= increase;
            *resultAddress = sFrmPlttVramManager.highAddress;
            return 1;
        }
    }
    return 0;
}

NNSGfdPlttKey NNS_GfdAllocFrmPlttVram(
    u32 size,
    BOOL fourColor,
    u32 allocationSide
)
{
    u32 address = 0;
    BOOL allocated = 0;

    size = RoundupPaletteSize(size);
    if (size >= NNS_GFD_PLTTSIZE_MAX) {
        return NNS_GFD_ALLOC_ERROR_PLTTKEY;
    }

    if (allocationSide == NNS_GFD_ALLOC_FROM_LOW) {
        allocated = AllocatePaletteLow(size, fourColor, &address);
    } else {
        allocated = AllocatePaletteHigh(size, fourColor, &address);
    }

    if (allocated) {
        return MakePaletteKey(address, size);
    }
    return NNS_GFD_ALLOC_ERROR_PLTTKEY;
}
