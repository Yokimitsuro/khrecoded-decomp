#include "nitro/types.h"

typedef struct {
    u32 pixelFmt;
    u32 mapingType;
    u32 characterFmt;
    u32 unk_0C;
    u32 szByte;
    void *pRawData;
} CharacterData;

typedef struct {
    u32 active;
    u8 modeState[0xc];
    s32 layout;
    u8 pad_14[0xe4];
    BOOL skipLoad;
} ActiveContext;

extern ActiveContext *data_ov001_020a04e4;

extern void *func_ov027_020ba1f8(void *resource);
extern void func_ov027_020ba200(void *resource, BOOL freeData);
extern BOOL NNS_G2dGetUnpackedBGCharacterData(void *file, CharacterData **out);
extern void DrawCategoryLabel(void *charData, int layout);
extern void DC_FlushAll(void);
extern void GX_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void LoadMenuEntryGraphic(void *modeState, int layout);

void LoadModeBg1Characters(void *resource)
{
    ActiveContext *context = data_ov001_020a04e4;
    CharacterData *charData;

    if (context->skipLoad) {
        func_ov027_020ba200(resource, TRUE);
        return;
    }
    NNS_G2dGetUnpackedBGCharacterData(func_ov027_020ba1f8(resource), &charData);
    DrawCategoryLabel(charData->pRawData, context->layout);
    DC_FlushAll();
    GX_LoadBG1Char(charData->pRawData, 0x1c00, 0x3840);
    LoadMenuEntryGraphic(context->modeState, context->layout);
    func_ov027_020ba200(resource, TRUE);
}
