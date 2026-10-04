typedef unsigned long u32;
typedef unsigned short u16;
typedef int BOOL;

#define TRUE 1
#define FALSE 0
#define NULL ((void *)0)
#define NNS_GFD_TEXSIZE_MIN 0x10
#define NNS_GFD_TEXSIZE_MAX 0x7fff0
#define NNS_GFD_ALLOC_ERROR_TEXKEY 0

typedef u32 NNSGfdTexKey;

typedef struct NNSGfdFrmTexRegionState {
    u32 head;
    u32 tail;
    BOOL active;
    const BOOL halfSize;
    const u16 index;
    const u16 padding;
    const u32 baseAddress;
} NNSGfdFrmTexRegionState;

extern NNSGfdFrmTexRegionState *sFrmTexVramRegionOrder[2];
extern NNSGfdFrmTexRegionState *sFrmTexVramNormalRegions[5];
extern NNSGfdFrmTexRegionState sFrmTexVramRegions[5];

static inline u32 RoundupTextureSize(u32 size)
{
    if (size == 0) {
        return NNS_GFD_TEXSIZE_MIN;
    }
    return (size + 0xf) & ~0xf;
}

static inline NNSGfdTexKey MakeTextureKey(u32 address, u32 size, BOOL compressed)
{
    return ((size >> 4) << 16) | (0xffff & (address >> 3)) | compressed << 31;
}

static inline u32 GetRegionCapacity(const NNSGfdFrmTexRegionState *region)
{
    (void)0;
    (void)0;
    return (u32)(region->tail - region->head);
}

static inline u32 AllocateFromRegionHead(NNSGfdFrmTexRegionState *region, u32 size)
{
    (void)0;
    (void)0;
    (void)0;
    {
        const u32 result = region->head;
        region->head += size;
        return result;
    }
}

static inline u32 AllocateFromRegionTail(NNSGfdFrmTexRegionState *region, u32 size)
{
    (void)0;
    (void)0;
    (void)0;
    {
        region->tail -= size;
        return region->tail;
    }
}

static inline NNSGfdFrmTexRegionState *GetCompressedIndexRegion(const NNSGfdFrmTexRegionState *region)
{
    (void)0;
    switch (region->index) {
    case 0:
        return &sFrmTexVramRegions[1];
    case 3:
        return &sFrmTexVramRegions[2];
    default:
        (void)0;
        break;
    }
    return NULL;
}

static inline BOOL AllocateCompressedTexture(u32 size, u32 *address)
{
    (void)0;
    (void)0;
    {
        int i;
        NNSGfdFrmTexRegionState *region = NULL;
        NNSGfdFrmTexRegionState *indexRegion = NULL;

        for (i = 0; i < 2; i++) {
            region = sFrmTexVramRegionOrder[i];
            if (region->active && GetRegionCapacity(region) >= size) {
                switch (region->index) {
                case 0:
                    indexRegion = &sFrmTexVramRegions[1];
                    break;
                case 3:
                    indexRegion = &sFrmTexVramRegions[2];
                    break;
                default:
                    indexRegion = NULL;
                    break;
                }
                if (indexRegion->active && GetRegionCapacity(indexRegion) >= size / 2) {
                    *address = AllocateFromRegionHead(region, size);
                    (void)AllocateFromRegionHead(indexRegion, size / 2);
                    *address += region->baseAddress;
                    return TRUE;
                }
            }
        }
        (void)0;
        return FALSE;
    }
}

static inline BOOL AllocateNormalTexture(u32 size, u32 *address)
{
    (void)0;
    (void)0;
    {
        int i;
        NNSGfdFrmTexRegionState *region = NULL;

        for (i = 0; i < 5; i++) {
            region = sFrmTexVramNormalRegions[i];
            if (region->active) {
                if (GetRegionCapacity(region) >= size) {
                    *address = AllocateFromRegionTail(region, size);
                    *address += region->baseAddress;
                    return TRUE;
                }
            }
        }
        (void)0;
        return FALSE;
    }
}

NNSGfdTexKey NNS_GfdAllocFrmTexVram(u32 size, BOOL compressed, u32 option)
{
#pragma unused(option)
    u32 address;
    BOOL allocated;

    (void)0;
    {
        size = RoundupTextureSize(size);
        if (size >= NNS_GFD_TEXSIZE_MAX) {
            (void)0;
            return NNS_GFD_ALLOC_ERROR_TEXKEY;
        }
        (void)0;
    }

    if (compressed) {
        allocated = AllocateCompressedTexture(size, &address);
    } else {
        allocated = AllocateNormalTexture(size, &address);
    }

    if (allocated) {
        return MakeTextureKey(address, size, compressed);
    } else {
        (void)0;
        return NNS_GFD_ALLOC_ERROR_TEXKEY;
    }
}