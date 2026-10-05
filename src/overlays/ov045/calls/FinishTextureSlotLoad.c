#include "nitro/types.h"

typedef struct {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy;
    u16 ofsEntry;
} ResDict;

typedef struct {
    u8 pad00[8];
    u32 texVramKey;
    u8 pad0c[0xc];
    u32 tex4x4VramKey;
    u8 pad1c[0x10];
    u32 plttVramKey;
    u16 sizePltt;
    u16 plttFlag;
    u16 plttOfsDict;
    u8 pad36[6];
    ResDict dict;
} ResTex;

typedef struct {
    u32 imageParam;
    u32 extraParam;
} TexEntry;

typedef struct {
    u16 offset;
    u16 flag;
} PlttEntry;

typedef struct {
    u16 width;
    u16 height;
    u32 imageParam;
    u32 plttBase;
    void *file;
} TextureSlot;

extern void func_0202c6a4(int mode);
extern s32 ValidateResourceTagAndDispatch(void *resource, void *heap);
extern ResTex *NNS_G3dGetTex(void *file);
extern void NNSi_FndFreeFromDefaultHeap(void *memory);

static inline void *GetDictEntry(const ResDict *dict, u32 index)
{
    if (dict != NULL && index < dict->numEntry) {
        return (u8 *)dict + dict->ofsEntry + 4;
    }
    return NULL;
}

void FinishTextureSlotLoad(TextureSlot *slot)
{
    ResTex *tex;
    TexEntry *texEntry = NULL;
    PlttEntry *plttEntry;
    u16 plttOffset;
    u16 texKey;
    u16 plttKey;

    func_0202c6a4(0);
    ValidateResourceTagAndDispatch(slot->file, NULL);
    func_0202c6a4(1);
    tex = NNS_G3dGetTex(slot->file);
    if (tex != NULL) {
        texEntry = GetDictEntry((ResDict *)((u8 *)tex + 0x3c), 0);
    }
    if (tex != NULL && tex->plttOfsDict != 0) {
        plttEntry = GetDictEntry((ResDict *)((u8 *)tex + tex->plttOfsDict), 0);
    } else {
        plttEntry = NULL;
    }
    plttKey = tex->plttVramKey;
    plttOffset = plttEntry->offset;
    if ((u8)((texEntry->imageParam & 0x1c000000) >> 26) == 5) {
        texKey = tex->tex4x4VramKey;
    } else {
        texKey = tex->texVramKey;
    }
    if (!(plttEntry->flag & 1)) {
        plttOffset >>= 1;
        plttKey >>= 1;
    }
    slot->width = texEntry->extraParam & 0x7ff;
    slot->height = (texEntry->extraParam >> 11) & 0x7ff;
    slot->imageParam = (texEntry->imageParam + texKey) | 0x20000000;
    slot->plttBase = (u16)(plttOffset + plttKey);
    NNSi_FndFreeFromDefaultHeap(slot->file);
    slot->file = NULL;
}



