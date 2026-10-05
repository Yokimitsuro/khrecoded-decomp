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
    VecFx32 prmBaseTrans;
    char padc4[0xd4 - 0xc4];
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
#define GX_TEXGEN_VERTEX 3
#define NNS_G3D_MTXSTACK_SYS 30
#define GX_MTXMODE_PROJECTION 0
#define GX_MTXMODE_POSITION_VECTOR 2
#define GX_MTXMODE_TEXTURE         3
#define G3OP_MTX_MODE     0x10
#define G3OP_MTX_STORE    0x13
#define G3OP_MTX_RESTORE  0x14
#define G3OP_MTX_LOAD_4x4 0x16
#define G3OP_MTX_MULT_4x3 0x19
#define G3OP_MTX_TRANS    0x1c
#define G3OP_MTX_MULT_4x4 0x18
#define G3OP_MTX_MULT_3x3 0x1a
#define G3OP_MTX_SCALE    0x1b
#define G3OP_TEXCOORD     0x22
#define GX_FX16ST(x) ((short)((x) >> 8))
#define GX_ST(s, t) ((u32)((u16)GX_FX16ST(s) | ((u16)GX_FX16ST(t) << 16)))
#define GX_PACK_TEXCOORD_PARAM(s, t) (GX_ST((s), (t)))

extern u32 data_02056050[];
extern u32 data_02056054[];
extern MtxFx44 data_02056060;
extern NNSG3dGlb NNS_G3dGlb;

extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 num);
extern void NNS_G3dGetCurrentMtx(MtxFx43 *m, MtxFx33 *n);
extern void GXi_FlushCommandList(void);
extern const MtxFx43 *NNS_G3dGlbGetInvV(void);
extern int G3X_GetClipMtx(MtxFx44 *m);

#define reg_G3_MTX_MODE     (*(volatile u32 *)0x04000440)
#define reg_G3_MTX_PUSH     (*(volatile u32 *)0x04000444)
#define reg_G3_MTX_POP      (*(volatile u32 *)0x04000448)
#define reg_G3_MTX_IDENTITY (*(volatile u32 *)0x04000454)

static inline void G3_MtxMode(u32 mode)
{
    reg_G3_MTX_MODE = mode;
}

static inline void G3_PushMtx(void)
{
    reg_G3_MTX_PUSH = 0;
}

static inline void G3_PopMtx(int num)
{
    reg_G3_MTX_POP = (u32)num;
}

static inline void G3_Identity(void)
{
    reg_G3_MTX_IDENTITY = 0;
}

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_MODE, (u32 *)&mode, 1);
}

static inline void NNS_G3dGeStoreMtx(int num)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_STORE, (u32 *)&num, 1);
}

static inline void NNS_G3dGeRestoreMtx(int num)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_RESTORE, (u32 *)&num, 1);
}

static inline void NNS_G3dGeTranslateVec(const VecFx32 *vec)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_TRANS, (u32 *)vec, 3);
}

static inline void NNS_G3dGeLoadMtx44(const MtxFx44 *m)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_LOAD_4x4, (u32 *)m, 16);
}

static inline void NNS_G3dGeMultMtx43(const MtxFx43 *m)
{
    NNS_G3dGeBufferOP_N(G3OP_MTX_MULT_4x3, (u32 *)m, 12);
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

void NNSi_G3dFuncSbc_PRJMAP(NNSG3dRS *rs)
{
    if ((rs->flag & (NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW | NNS_G3D_RSFLAG_NODE_VISIBLE)) == NNS_G3D_RSFLAG_NODE_VISIBLE) {
        MtxFx43 m;

        NNS_G3dGetCurrentMtx(&m, 0);
        NNS_G3dGeStoreMtx(NNS_G3D_MTXSTACK_SYS);

        if ((rs->pMatAnmResult->prmTexImage & REG_G3_TEXIMAGE_PARAM_TGEN_MASK) !=
            (GX_TEXGEN_VERTEX << REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT)) {
            rs->pMatAnmResult->prmTexImage &= ~REG_G3_TEXIMAGE_PARAM_TGEN_MASK;
            rs->pMatAnmResult->prmTexImage |= GX_TEXGEN_VERTEX << REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT;

            data_02056050[1] = rs->pMatAnmResult->prmTexImage;
            NNS_G3dGeBufferOP_N(data_02056050[0], data_02056054, 1);
        }

        {
            s32 width, height;

            width = (s32)rs->pMatAnmResult->origWidth;
            height = (s32)rs->pMatAnmResult->origHeight;

            {
                MtxFx44 *mtx = &data_02056060;

                mtx->_00 = width << (12 + 3);
                mtx->_11 = -height << (12 + 3);
                mtx->_30 = width << (12 + 3);
                mtx->_31 = height << (12 + 3);

                NNS_G3dGeLoadMtx44(mtx);
            }
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
            MtxFx44 tex_mtx;

            if (NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_FLUSH_WVP) {
                NNS_G3dGeTranslateVec(&NNS_G3dGlb.prmBaseTrans);
                NNS_G3dGeMultMtx33(&NNS_G3dGlb.prmBaseRot);
                NNS_G3dGeMultMtx43(&m);
            } else if (NNS_G3dGlb.flag & NNS_G3D_GLB_FLAG_FLUSH_VP) {
                NNS_G3dGeMultMtx43(&m);
            } else {
                NNS_G3dGeMultMtx43(NNS_G3dGlbGetInvV());
                NNS_G3dGeMultMtx43(&m);
            }

            {
                GXi_FlushCommandList();

                G3_MtxMode(GX_MTXMODE_PROJECTION);
                G3_PushMtx();
                G3_Identity();

                while (G3X_GetClipMtx(&tex_mtx)) {
                }

                G3_PopMtx(1);
                G3_MtxMode(GX_MTXMODE_TEXTURE);
            }

            NNS_G3dGeLoadMtx44(&tex_mtx);
            NNS_G3dGeTexCoord(tex_mtx._30 >> 4, tex_mtx._31 >> 4);
        }

        NNS_G3dGeMtxMode(GX_MTXMODE_POSITION_VECTOR);
        NNS_G3dGeRestoreMtx(NNS_G3D_MTXSTACK_SYS);
    }
    rs->c += 3;
}
