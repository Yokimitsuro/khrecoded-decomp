#include "nitro/types.h"

typedef struct TextureDrawParams {
    u16 width;
    u16 height;
    u32 imageParam;
    u32 paletteBase;
} TextureDrawParams;

typedef struct ContextModel {
    u8 data[0x104];
} ContextModel;

typedef struct ResourceContext {
    u8 pad_000[0x10];
    TextureDrawParams texA;
    TextureDrawParams texB;
    TextureDrawParams texC;
    TextureDrawParams digits[10];
    TextureDrawParams texD;
    TextureDrawParams texE[2];
    TextureDrawParams texF[2];
    u8 pad_0E8[0x1e];
    u16 archiveIndex;
    u16 loadedMask;
    u8 pad_10A[0xae];
    ContextModel modelA;
    ContextModel modelB;
    TextureDrawParams texG;
    TextureDrawParams texH;
    ContextModel modelC;
    ContextModel modelD;
    u8 pad_5E0[0x20];
    ContextModel modelE;
    ContextModel modelF;
    ContextModel modelG;
} ResourceContext;

extern void func_0202c6a4(int useAltHandlers);
extern int func_ov001_02064784(void);
extern void LoadTextureDrawParamsFromArchive(ResourceContext *context, u32 fileIndex, TextureDrawParams *params, int count, int firstIndex);
extern void LoadCurrentArchiveModel(ResourceContext *context, u32 fileIndex, ContextModel *model);
extern void LoadCurrentArchiveModelFlagged(ResourceContext *context, u32 fileIndex, ContextModel *model);

void LoadResourceGroups(ResourceContext *context, u32 mask)
{
    u32 newMask;

    newMask = context->loadedMask ^ (context->loadedMask | mask);
    func_0202c6a4(0);
    if (newMask & 1) {
        context->archiveIndex = 0;
        LoadTextureDrawParamsFromArchive(context, 2, &context->texA, 1, 0);
        LoadTextureDrawParamsFromArchive(context, 3, &context->texB, 1, 0);
        LoadTextureDrawParamsFromArchive(context, 0, context->digits, 10, 0);
        LoadTextureDrawParamsFromArchive(context, 0, &context->texD, 1, 10);
        LoadTextureDrawParamsFromArchive(context, 1, context->texE, 2, 0);
    }
    if (newMask & 2) {
        context->archiveIndex = 1;
        LoadCurrentArchiveModel(context, 0, &context->modelA);
        if (func_ov001_02064784() == 6) {
            LoadCurrentArchiveModel(context, 0xb, &context->modelB);
            LoadTextureDrawParamsFromArchive(context, 0xc, &context->texH, 1, 0);
        } else {
            LoadCurrentArchiveModel(context, 1, &context->modelB);
        }
        LoadTextureDrawParamsFromArchive(context, 5, &context->texG, 1, 0);
    }
    if (newMask & 4) {
        context->archiveIndex = 1;
        LoadCurrentArchiveModel(context, 2, &context->modelC);
        LoadCurrentArchiveModel(context, 3, &context->modelD);
    }
    if (newMask & 8) {
        context->archiveIndex = 1;
        LoadTextureDrawParamsFromArchive(context, 7, &context->texC, 1, 0);
        LoadTextureDrawParamsFromArchive(context, 9, context->texF, 2, 0);
    }
    if (newMask & 0x10) {
        context->archiveIndex = 1;
        LoadCurrentArchiveModelFlagged(context, 4, &context->modelE);
    }
    if (newMask & 0x80) {
        context->archiveIndex = 1;
        LoadCurrentArchiveModelFlagged(context, 0xd, &context->modelF);
        LoadCurrentArchiveModelFlagged(context, 0xe, &context->modelG);
    }
    if (newMask & 0x20) {
        context->archiveIndex = 1;
        LoadTextureDrawParamsFromArchive(context, 6, &context->texC, 1, 0);
        LoadTextureDrawParamsFromArchive(context, 9, context->texF, 2, 0);
    }
    if (newMask & 0x40) {
        context->archiveIndex = 1;
        LoadTextureDrawParamsFromArchive(context, 8, &context->texC, 1, 0);
    }
    func_0202c6a4(1);
    context->loadedMask |= (u16)mask;
}
