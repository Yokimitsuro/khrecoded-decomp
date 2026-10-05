#ifndef G3D_KERNEL_INTERNAL_H
#define G3D_KERNEL_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef int BOOL;
typedef int fx32;
typedef short fx16;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0

#define NNS_G3D_ANMOBJ_MAPDATA_EXIST 0x0100
#define NNS_G3D_RENDEROBJ_FLAG_HINT_OBSOLETE 0x00000010
#define FX32_ONE 0x1000
#define NNS_GFD_TEXKEY_ADDR_SHIFT 3
#define REG_G3_TEXIMAGE_PARAM_TGEN_MASK 0xc0000000
#define REG_G3_TEXIMAGE_PARAM_FT_MASK 0x00080000
#define REG_G3_TEXIMAGE_PARAM_FS_MASK 0x00040000
#define REG_G3_TEXIMAGE_PARAM_RT_MASK 0x00020000
#define REG_G3_TEXIMAGE_PARAM_RS_MASK 0x00010000

typedef struct NNSG3dResMdl_ NNSG3dResMdl;

typedef struct NNSG3dResAnmHeader_ {
    u8 category0;
    u8 revision;
    u16 category1;
} NNSG3dResAnmHeader;

typedef struct NNSG3dResDataBlockHeader_ {
    union {
        u32 kind;
        char chr[4];
    };
    u32 size;
} NNSG3dResDataBlockHeader;

typedef struct NNSG3dResDictTreeNode_ {
    u8 refBit;
    u8 idxLeft;
    u8 idxRight;
    u8 idxEntry;
} NNSG3dResDictTreeNode;

typedef struct NNSG3dResDict_ {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;

typedef struct NNSG3dResTexInfo_ {
    u32 vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy_;
    u32 ofsTex;
} NNSG3dResTexInfo;

typedef struct NNSG3dResTex4x4Info_ {
    u32 vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy_;
    u32 ofsTex;
    u32 ofsTexPlttIdx;
} NNSG3dResTex4x4Info;

typedef struct NNSG3dResPlttInfo_ {
    u32 vramKey;
    u16 sizePltt;
    u16 flag;
    u16 ofsDict;
    u16 dummy_;
    u32 ofsPlttData;
} NNSG3dResPlttInfo;

typedef struct NNSG3dResTex_ {
    NNSG3dResDataBlockHeader header;
    NNSG3dResTexInfo texInfo;
    NNSG3dResTex4x4Info tex4x4Info;
    NNSG3dResPlttInfo plttInfo;
    NNSG3dResDict dict;
} NNSG3dResTex;

typedef struct NNSG3dResDictEntryHeader_ {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef union NNSG3dResName_ {
    char name[16];
    u32 val[4];
} NNSG3dResName;

typedef struct NNSG3dResDictTexData_ {
    u32 texImageParam;
    u32 extraParam;
} NNSG3dResDictTexData;

typedef struct NNSG3dResDictPlttData_ {
    u16 offset;
    u16 flag;
} NNSG3dResDictPlttData;

typedef struct NNSG3dResDictMatData_ {
    u32 offset;
} NNSG3dResDictMatData;

typedef struct NNSG3dResDictTexToMatIdxData_ {
    u16 offset;
    u8 numIdx;
    u8 flag;
} NNSG3dResDictTexToMatIdxData;

typedef struct NNSG3dResDictPlttToMatIdxData_ {
    u16 offset;
    u8 numIdx;
    u8 flag;
} NNSG3dResDictPlttToMatIdxData;

typedef struct NNSG3dResMatData_ {
    u16 itemTag;
    u16 size;
    u32 diffAmb;
    u32 specEmi;
    u32 polyAttr;
    u32 polyAttrMask;
    u32 texImageParam;
    u32 texImageParamMask;
    u16 texPlttBase;
    u16 flag;
    u16 origWidth;
    u16 origHeight;
    fx32 magW;
    fx32 magH;
} NNSG3dResMatData;

typedef struct NNSG3dResMat_ {
    u16 ofsDictTexToMatList;
    u16 ofsDictPlttToMatList;
    NNSG3dResDict dict;
} NNSG3dResMat;

typedef struct NNSG3dResMdlInfo_ {
    u8 sbcType;
    u8 scalingRule;
    u8 texMtxMode;
    u8 numNode;
    u8 numMat;
    u8 numShp;
    u8 firstUnusedMtxStackID;
    u8 dummy_;
    fx32 posScale;
    fx32 invPosScale;
    u16 numVertex;
    u16 numPolygon;
    u16 numTriangle;
    u16 numQuad;
    fx16 boxX;
    fx16 boxY;
    fx16 boxZ;
    fx16 boxW;
    fx16 boxH;
    fx16 boxD;
    fx32 boxPosScale;
    fx32 boxInvPosScale;
} NNSG3dResMdlInfo;

typedef struct NNSG3dResNodeInfo_ {
    NNSG3dResDict dict;
} NNSG3dResNodeInfo;

struct NNSG3dResMdl_ {
    u32 size;
    u32 ofsSbc;
    u32 ofsMat;
    u32 ofsShp;
    u32 ofsEvpMtx;
    NNSG3dResMdlInfo info;
    NNSG3dResNodeInfo nodeInfo;
};

extern void *NNS_G3dGetResDataByName(
    const NNSG3dResDict *dict,
    const NNSG3dResName *name);

#ifndef G3D_KERNEL_CUSTOM_RESOURCE_INLINE
static inline void *NNS_G3dGetResDataByIdx(
    const NNSG3dResDict *dict,
    u32 index)
{
    NNSG3dResDictEntryHeader *header;

    if (dict != NULL && index < dict->numEntry) {
        header = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return &header->data[0] + header->sizeUnit * index;
    }
    return NULL;
}

static inline const NNSG3dResName *NNS_G3dGetResNameByIdx(
    const NNSG3dResDict *dict,
    u32 index)
{
    NNSG3dResDictEntryHeader *header;

    if (dict != NULL && index < dict->numEntry) {
        header = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (NNSG3dResName *)((u8 *)header + header->ofsName +
                                 sizeof(NNSG3dResName) * index);
    }
    return NULL;
}

static inline NNSG3dResMatData *NNS_G3dGetMatDataByIdx(
    const NNSG3dResMat *mat,
    u32 index)
{
    NNSG3dResDictMatData *data;

    if (mat) {
        data = NNS_G3dGetResDataByIdx(&mat->dict, index);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return NULL;
}

static inline NNSG3dResMat *NNS_G3dGetMat(const NNSG3dResMdl *model)
{
    if (model && model->ofsMat != 0) {
        return (NNSG3dResMat *)((u8 *)model + model->ofsMat);
    }
    return NULL;
}

static inline NNSG3dResDictTexData *NNS_G3dGetTexDataByName(
    const NNSG3dResTex *tex,
    const NNSG3dResName *name)
{
    if (tex) {
        return NNS_G3dGetResDataByName(&tex->dict, name);
    }
    return NULL;
}

static inline NNSG3dResDictPlttData *NNS_G3dGetPlttDataByName(
    const NNSG3dResTex *tex,
    const NNSG3dResName *name)
{
    NNSG3dResDict *dict;

    if (tex && tex->plttInfo.ofsDict != 0) {
        dict = (NNSG3dResDict *)((u8 *)tex + tex->plttInfo.ofsDict);
        return NNS_G3dGetResDataByName(dict, name);
    }
    return NULL;
}

static inline u32 NNS_GfdGetTexKeyAddr(u32 key)
{
    return (key & 0xffff) << NNS_GFD_TEXKEY_ADDR_SHIFT;
}
#endif

typedef struct NNSG3dAnmObj_ {
    fx32 frame;
    fx32 ratio;
    void *resAnm;
    void *funcAnm;
    struct NNSG3dAnmObj_ *next;
    const NNSG3dResTex *resTex;
    u8 priority;
    u8 numMapData;
    u16 mapData[1];
} NNSG3dAnmObj;

struct NNSG3dMatAnmResult_;
struct NNSG3dJntAnmResult_;
struct NNSG3dVisAnmResult_;
struct NNSG3dRS_;

typedef BOOL (*NNSG3dFuncAnmBlendMat)(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
typedef BOOL (*NNSG3dFuncAnmBlendJnt)(
    struct NNSG3dJntAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
typedef BOOL (*NNSG3dFuncAnmBlendVis)(
    struct NNSG3dVisAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
typedef void (*NNSG3dSbcCallBackFunc)(struct NNSG3dRS_ *);

typedef struct NNSG3dRenderObj_ {
    u32 flag;
    NNSG3dResMdl *resMdl;
    NNSG3dAnmObj *anmMat;
    NNSG3dFuncAnmBlendMat funcBlendMat;
    NNSG3dAnmObj *anmJnt;
    NNSG3dFuncAnmBlendJnt funcBlendJnt;
    NNSG3dAnmObj *anmVis;
    NNSG3dFuncAnmBlendVis funcBlendVis;
    NNSG3dSbcCallBackFunc cbFunc;
    u8 cbCmd;
    u8 cbTiming;
    u16 dummy_;
    NNSG3dSbcCallBackFunc cbInitFunc;
    void *ptrUser;
    u8 *ptrUserSbc;
    struct NNSG3dJntAnmResult_ *recJntAnm;
    struct NNSG3dMatAnmResult_ *recMatAnm;
    u32 hintMatAnmExist[2];
    u32 hintJntAnmExist[2];
    u32 hintVisAnmExist[2];
} NNSG3dRenderObj;

typedef void (*NNSG3dAnimInitFunc)(
    NNSG3dAnmObj *,
    void *,
    const NNSG3dResMdl *);

typedef struct NNSG3dAnmObjInitFunc_ {
    u8 category0;
    u8 dummy_;
    u16 category1;
    NNSG3dAnimInitFunc func;
} NNSG3dAnmObjInitFunc;

static inline void NNS_G3dRenderObjSetFlag(
    NNSG3dRenderObj *pRenderObj,
    u32 flag)
{
    pRenderObj->flag |= flag;
}

#endif
