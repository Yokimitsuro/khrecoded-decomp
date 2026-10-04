#ifndef GFD_LINKED_LIST_VRAM_MAN_TYPES_H
#define GFD_LINKED_LIST_VRAM_MAN_TYPES_H

#include "libs/nns/gfd/gfdi_LinkedListVramMan_Common.h"

typedef u32 NNSGfdTexKey;
typedef u32 NNSGfdPlttKey;

typedef struct NNS_GfdLnkTexVramManager {
    NNSiGfdLnkVramMan normalManager;
    NNSiGfdLnkVramMan compressedManager;
    NNSiGfdLnkVramBlock *blockPoolList;
    u32 size;
    u32 compressedSize;
    NNSiGfdLnkVramBlock *work;
    u32 workSize;
} NNS_GfdLnkTexVramManager;

typedef struct NNS_GfdLnkPlttVramManager {
    NNSiGfdLnkVramMan manager;
    NNSiGfdLnkVramBlock *blockPoolList;
    u32 size;
    NNSiGfdLnkVramBlock *work;
    u32 workSize;
} NNS_GfdLnkPlttVramManager;

typedef struct GfdLnkTexSlotData {
    u32 freeSize;
    u32 normalSize;
    u32 compressedSize;
} GfdLnkTexSlotData;

extern NNS_GfdLnkTexVramManager sLnkTexVramManager;
extern NNS_GfdLnkPlttVramManager sLnkPlttVramManager;

extern NNSGfdTexKey (*sDefaultAllocTexVramFunc)(u32, BOOL, u32);
extern int (*sDefaultFreeTexVramFunc)(NNSGfdTexKey);
extern NNSGfdPlttKey (*sDefaultAllocPlttVramFunc)(u32, BOOL, u32);
extern int (*sDefaultFreePlttVramFunc)(NNSGfdPlttKey);

extern void NNS_GfdResetLnkTexVramState(void);
extern NNSGfdTexKey NNS_GfdAllocLnkTexVram(u32, BOOL, u32);
extern int NNS_GfdFreeLnkTexVram(NNSGfdTexKey);
extern void NNS_GfdResetLnkPlttVramState(void);
extern NNSGfdPlttKey NNS_GfdAllocLnkPlttVram(u32, BOOL, u32);
extern int NNS_GfdFreeLnkPlttVram(NNSGfdPlttKey);

extern BOOL NNSi_GfdAllocLnkVram(NNSiGfdLnkVramMan *, NNSiGfdLnkVramBlock **, u32 *, u32);
extern BOOL NNSi_GfdAllocLnkVramAligned(NNSiGfdLnkVramMan *, NNSiGfdLnkVramBlock **, u32 *, u32, u32);
extern BOOL NNSi_GfdFreeLnkVram(NNSiGfdLnkVramMan *, NNSiGfdLnkVramBlock **, u32, u32);

static inline u32 GfdRoundupTexSize_(u32 size)
{
    return size == 0 ? 0x10 : (size + 0xf) & ~0xf;
}

static inline u32 GfdRoundupPlttSize_(u32 size)
{
    return size == 0 ? 8 : (size + 7) & ~7;
}

#endif
