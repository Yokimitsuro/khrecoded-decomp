#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/hw.h"

#define REG_G3_TEXIMAGE_PARAM_TGEN_MASK 0xc0000000
#define REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT 30

typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22; } MtxFx33;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22, _30, _31, _32; } MtxFx43;
typedef struct {
    fx32 _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33;
} MtxFx44;

typedef struct NNSG3dResDict {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
} NNSG3dResDict;

typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit;
    u16 sizeName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct NNSG3dResDictMatData {
    u32 offset;
} NNSG3dResDictMatData;

typedef struct NNSG3dResMat {
    u16 ofsDictTexToMatList;
    u16 ofsDictPlttToMatList;
    NNSG3dResDict dict;
} NNSG3dResMat;

typedef struct NNSG3dResMatData {
    char pad00[0x1e];
    u16 flag;
    char pad20[0x2c - 0x20];
} NNSG3dResMatData;

typedef struct NNSG3dMatAnmResult {
    char pad00[0x10];
    u32 prmTexImage;
    char pad14[0x2c - 0x14];
    u16 origWidth;
    u16 origHeight;
} NNSG3dMatAnmResult;

typedef struct NNSG3dRS {
    const u8 *c;
    u32 pad04;
    u32 flag;
    char pad0c[0xb0 - 0x0c];
    NNSG3dMatAnmResult *pMatAnmResult;
    char padb4[0xd8 - 0xb4];
    const NNSG3dResMat *pResMat;
} NNSG3dRS;

typedef struct NNSG3dGlb {
    char pad00[0x4c];
    MtxFx43 cameraMtx;
    char pad7c[0x94 - 0x7c];
    MtxFx33 prmBaseRot;
    char padb8[0xd4 - 0xb8];
    u32 flag;
} NNSG3dGlb;

#define NNS_G3D_RSFLAG_NODE_VISIBLE     0x001
#define NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW 0x200
#define NNS_G3D_GLB_FLAG_FLUSH_WVP 1
#define NNS_G3D_GLB_FLAG_FLUSH_VP  2
#define NNS_G3D_MATFLAG_TEXMTX_SCALEONE  0x0002
#define NNS_G3D_MATFLAG_TEXMTX_ROTZERO   0x0004
#define NNS_G3D_MATFLAG_TEXMTX_TRANSZERO 0x0008
#define NNS_G3D_MATFLAG_EFFECTMTX        0x2000
#define GX_TEXGEN_NORMAL 2
#define GX_MTXMODE_POSITION_VECTOR 2
#define GX_MTXMODE_TEXTURE         3
#define G3OP_MTX_MODE     0x10
#define G3OP_MTX_MULT_4x4 0x18
#define G3OP_MTX_MULT_3x3 0x1a
#define G3OP_MTX_SCALE    0x1b
#define G3OP_TEXCOORD     0x22
#define GX_FX16ST(x) ((short)((x) >> 8))
#define GX_ST(s, t) ((u32)((u16)GX_FX16ST(s) | ((u16)GX_FX16ST(t) << 16)))
#define GX_PACK_TEXCOORD_PARAM(s, t) (GX_ST((s), (t)))

extern u32 data_02056050[];
extern u32 data_0205605c[];
extern NNSG3dGlb NNS_G3dGlb;

extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 num);
extern void NNS_G3dGetCurrentMtx(MtxFx43 *m, MtxFx33 *n);

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_MODE, (u32 *)&mode, 1);
}

static inline void NNS_G3dGeScale(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    NNS_G3dGeBufferOP_N(G3OP_MTX_SCALE, (u32 *)&vec, 3);
}

static inline void NNS_G3dGeTexCoord(fx32 s, fx32 t)
{
    u32 tmp;

    tmp = GX_PACK_TEXCOORD_PARAM(s, t);
    NNS_G3dGeBufferOP_N(G3OP_TEXCOORD, (u32 *)&tmp, 1);
}

static inline void NNS_G3dGeMultMtx44(const MtxFx44 *m)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_MULT_4x4, (u32 *)m, 16);
}

static inline void NNS_G3dGeMultMtx33(const MtxFx33 *m)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_MULT_3x3, (u32 *)m, 9);
}

static inline void *NNS_G3dGetResDataByIdx(const NNSG3dResDict *dict, u32 idx)
{
    NNSG3dResDictEntryHeader *hdr;

    if (dict != 0 && idx < dict->numEntry) {
        hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)(&hdr->data[0] + hdr->sizeUnit * idx);
    } else {
        return 0;
    }
}

static inline NNSG3dResMatData *NNS_G3dGetMatDataByIdx(const NNSG3dResMat *mat, u32 idx)
{
    NNSG3dResDictMatData *data;

    if (mat) {
        data = (NNSG3dResDictMatData *)NNS_G3dGetResDataByIdx(&mat->dict, idx);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return 0;
}

void NNSi_G3dFuncSbc_ENVMAP(NNSG3dRS *rs)
{
    if (!(rs->flag & NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW) && (rs->flag & NNS_G3D_RSFLAG_NODE_VISIBLE)) {
        if ((rs->pMatAnmResult->prmTexImage & REG_G3_TEXIMAGE_PARAM_TGEN_MASK) !=
            (GX_TEXGEN_NORMAL << REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT)) {
            rs->pMatAnmResult->prmTexImage &= ~REG_G3_TEXIMAGE_PARAM_TGEN_MASK;
            rs->pMatAnmResult->prmTexImage |= GX_TEXGEN_NORMAL << REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT;

            data_02056050[3] = rs->pMatAnmResult->prmTexImage;
            NNS_G3dGeBufferOP_N(data_02056050[2], data_0205605c, 1);
        }

        NNS_G3dGeMtxMode(GX_MTXMODE_TEXTURE);

        {
            s32 width, height;

            width = (s32)rs->pMatAnmResult->origWidth;
            height = (s32)rs->pMatAnmResult->origHeight;

            NNS_G3dGeScale(width << (12 + 3), -height << (12 + 3), 0x1000 << 4);
            NNS_G3dGeTexCoord(width << (12 - 1), height << (12 - 1));
        }

        {
            u32 idxMat = *(rs->c + 1);
            const NNSG3dResMatData *mat = NNS_G3dGetMatDataByIdx(rs->pResMat, idxMat);

            if (mat->flag & NNS_G3D_MATFLAG_EFFECTMTX) {
                const MtxFx44 *effect_mtx;
                const u8 *p = (const u8 *)mat + sizeof(NNSG3dResMatData);

                if (!(mat->flag & NNS_G3D_MATFLAG_TEXMTX_SCALEONE)) {
                    p += sizeof(fx32) + sizeof(fx32);
                }
                if (!(mat->flag & NNS_G3D_MATFLAG_TEXMTX_ROTZERO)) {
                    p += sizeof(short) + sizeof(short);
                }
                if (!(mat->flag & NNS_G3D_MATFLAG_TEXMTX_TRANSZERO)) {
                    p += sizeof(fx32) + sizeof(fx32);
                }
                effect_mtx = (const MtxFx44 *)p;
                NNS_G3dGeMultMtx44(effect_mtx);
            }
        }

        {
            MtxFx33 n;

            NNS_G3dGeMtxMode(GX_MTXMODE_POSITION_VECTOR);
            NNS_G3dGetCurrentMtx(0, &n);
            NNS_G3dGeMtxMode(GX_MTXMODE_TEXTURE);

            if (NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
                NNS_G3dGeMultMtx33((const MtxFx33 *)&NNS_G3dGlb.cameraMtx);
                NNS_G3dGeMultMtx33(&NNS_G3dGlb.prmBaseRot);
                NNS_G3dGeMultMtx33(&n);
            } else if (NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
                NNS_G3dGeMultMtx33((const MtxFx33 *)&NNS_G3dGlb.cameraMtx);
                NNS_G3dGeMultMtx33(&n);
            } else {
                NNS_G3dGeMultMtx33(&n);
            }
        }

        NNS_G3dGeMtxMode(GX_MTXMODE_POSITION_VECTOR);
    }
    rs->c += 3;
}
