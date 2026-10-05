#include "nitro/types.h"
#include "nnsys/g3d.h"

#define SIGNATURE_NSBMD 0x30444d42

typedef NNSGfdPlttKey (*PlttVramAllocFunc)(u32 size, BOOL is4Pltt, u32 fromLow);
typedef int (*PlttVramFreeFunc)(NNSGfdPlttKey key);

extern BOOL data_02056014;
extern NNSGfdFuncAllocTexVram sDefaultAllocTexVramFunc;
extern NNSGfdFuncFreeTexVram sDefaultFreeTexVramFunc;
extern PlttVramAllocFunc sDefaultAllocPlttVramFunc;
extern PlttVramFreeFunc sDefaultFreePlttVramFunc;

extern NNSG3dResTex *NNS_G3dGetTex(void *file);
extern u32 NNS_G3dTexGetRequiredSize(const NNSG3dResTex *tex);
extern u32 NNS_G3dTex4x4GetRequiredSize(const NNSG3dResTex *tex);
extern u32 NNS_G3dPlttGetRequiredSize(const NNSG3dResTex *tex);
extern void NNS_G3dTexSetTexKey(NNSG3dResTex *tex, NNSGfdTexKey texKey, NNSGfdTexKey tex4x4Key);
extern void Obj_SetWord2C(NNSG3dResTex *tex, NNSGfdPlttKey plttKey);
extern void Tex_LoadVram(NNSG3dResTex *tex);
extern void func_0202d218(NNSG3dResTex *tex);
extern void *NNS_G3dGetMdlSet(void *file);
extern BOOL NNS_G3dBindMdlSet(void *mdlSet, const NNSG3dResTex *tex);

BOOL SetupResourceTextures(u32 signature, void *file, NNSG3dResTex *tex)
{
    if (data_02056014) {
        u32 texSize;
        u32 tex4x4Size;
        u32 plttSize;
        BOOL texOk = TRUE;
        BOOL tex4x4Ok = TRUE;
        BOOL plttOk = TRUE;
        NNSGfdTexKey texKey;
        NNSGfdTexKey tex4x4Key;
        NNSGfdPlttKey plttKey;

        if (tex == NULL) {
            tex = NNS_G3dGetTex(file);
        }
        if (tex != NULL) {
            texSize = NNS_G3dTexGetRequiredSize(tex);
            tex4x4Size = NNS_G3dTex4x4GetRequiredSize(tex);
            plttSize = NNS_G3dPlttGetRequiredSize(tex);

            if (texSize > 0) {
                texKey = sDefaultAllocTexVramFunc(texSize, FALSE, 0);
                if (texKey == 0) {
                    texOk = FALSE;
                }
            } else {
                texKey = 0;
            }

            if (tex4x4Size > 0) {
                tex4x4Key = sDefaultAllocTexVramFunc(tex4x4Size, TRUE, 0);
                if (tex4x4Key == 0) {
                    tex4x4Ok = FALSE;
                }
            } else {
                tex4x4Key = 0;
            }

            if (plttSize > 0) {
                plttKey = sDefaultAllocPlttVramFunc(plttSize, tex->tex4x4Info.flag & 0x8000, 0);
                if (plttKey == 0) {
                    plttOk = FALSE;
                }
            } else {
                plttKey = 0;
            }

            if (!texOk || !tex4x4Ok || !plttOk) {
                sDefaultFreePlttVramFunc(plttKey);
                sDefaultFreeTexVramFunc(tex4x4Key);
                sDefaultFreeTexVramFunc(texKey);
                return FALSE;
            }

            NNS_G3dTexSetTexKey(tex, texKey, tex4x4Key);
            Obj_SetWord2C(tex, plttKey);
            Tex_LoadVram(tex);
            func_0202d218(tex);
        }

        if (signature == SIGNATURE_NSBMD) {
            void *mdlSet = NNS_G3dGetMdlSet(file);

            if (tex != NULL) {
                NNS_G3dBindMdlSet(mdlSet, tex);
            }
        }
    }
    return TRUE;
}
