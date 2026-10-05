typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
typedef u32 NNSGfdTexKey;
typedef u32 NNSGfdPlttKey;
typedef u32 NNSG3dTexKey;
typedef u32 NNSG3dPlttKey;

typedef struct NNSG3dResTex NNSG3dResTex;
typedef struct NNSG3dResMdlSet NNSG3dResMdlSet;
typedef struct NNSG3dResFileHeader NNSG3dResFileHeader;

typedef int (*NNSGfdFuncFreeTexVram)(NNSGfdTexKey);
typedef int (*NNSGfdFuncFreePlttVram)(NNSGfdPlttKey);

#define FALSE 0

#define NNS_G3D_SIGNATURE_NSBMD '0DMB'
#define NNS_G3D_SIGNATURE_NSBTX '0XTB'
#define NNS_G3D_SIGNATURE_NSBCA '0ACB'
#define NNS_G3D_SIGNATURE_NSBVA '0AVB'
#define NNS_G3D_SIGNATURE_NSBMA '0AMB'
#define NNS_G3D_SIGNATURE_NSBTP '0PTB'
#define NNS_G3D_SIGNATURE_NSBTA '0ATB'

extern NNSGfdFuncFreeTexVram sDefaultFreeTexVramFunc;

inline int NNS_GfdFreeTexVram(NNSGfdTexKey memKey)
{
    return (*sDefaultFreeTexVramFunc)(memKey);
}

extern NNSGfdFuncFreePlttVram sDefaultFreePlttVramFunc;

inline int NNS_GfdFreePlttVram(NNSGfdPlttKey plttKey)
{
    return (*sDefaultFreePlttVramFunc)(plttKey);
}

void NNS_G3dTexReleaseTexKey(NNSG3dResTex *tex, NNSG3dTexKey *texKey, NNSG3dTexKey *tex4x4Key);
NNSG3dPlttKey NNS_G3dPlttReleasePlttKey(NNSG3dResTex *tex);
void NNS_G3dReleaseMdlSet(NNSG3dResMdlSet *mdlSet);
NNSG3dResMdlSet *NNS_G3dGetMdlSet(const NNSG3dResFileHeader *header);
NNSG3dResTex *NNS_G3dGetTex(const NNSG3dResFileHeader *header);

void NNS_G3dResDefaultRelease(void *pResData)
{
    u8 *binFile = (u8 *)pResData;
    BOOL failed = FALSE;

    switch (*(u32 *)&binFile[0]) {
    case NNS_G3D_SIGNATURE_NSBMD:
    {
        NNSG3dResTex *tex;
        NNSG3dResMdlSet *mdlSet = NNS_G3dGetMdlSet(pResData);
        tex = NNS_G3dGetTex((NNSG3dResFileHeader *)pResData);

        if (tex) {
            NNS_G3dReleaseMdlSet(mdlSet);
        }
    }

    case NNS_G3D_SIGNATURE_NSBTX:
    {
        NNSG3dResTex *tex;
        NNSG3dPlttKey plttKey;
        NNSG3dTexKey texKey, tex4x4Key;
        int status;
        tex = NNS_G3dGetTex((NNSG3dResFileHeader *)pResData);

        if (tex) {
            plttKey = NNS_G3dPlttReleasePlttKey(tex);
            NNS_G3dTexReleaseTexKey(tex, &texKey, &tex4x4Key);

            if (plttKey > 0) {
                status = NNS_GfdFreePlttVram(plttKey);
            }

            if (tex4x4Key > 0) {
                status = NNS_GfdFreeTexVram(tex4x4Key);
            }

            if (texKey > 0) {
                status = NNS_GfdFreeTexVram(texKey);
            }
        }
    }
    break;
    case NNS_G3D_SIGNATURE_NSBCA:
    case NNS_G3D_SIGNATURE_NSBVA:
    case NNS_G3D_SIGNATURE_NSBMA:
    case NNS_G3D_SIGNATURE_NSBTP:
    case NNS_G3D_SIGNATURE_NSBTA:
        break;
    default:
        break;
    }
}
