#ifndef G3D_KERNEL_INTERNAL_H
#define G3D_KERNEL_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef int fx32;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0

#define NNS_G3D_ANMOBJ_MAPDATA_EXIST 0x0100
#define NNS_G3D_RENDEROBJ_FLAG_HINT_OBSOLETE 0x00000010

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
