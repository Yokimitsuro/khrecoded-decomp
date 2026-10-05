#include "libs/nns/g3d/g3d_kernel_internal.h"

typedef void (*NNSG3dFuncAnmMat)(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
typedef void (*NNSG3dFuncAnmJnt)(
    struct NNSG3dJntAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
typedef void (*NNSG3dFuncAnmVis)(
    struct NNSG3dVisAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);

extern BOOL NNSi_G3dAnmBlendMat(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern BOOL NNSi_G3dAnmBlendJnt(
    struct NNSG3dJntAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern BOOL NNSi_G3dAnmBlendVis(
    struct NNSG3dVisAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void NNSi_G3dAnmObjInitNsBca(
    NNSG3dAnmObj *,
    void *,
    const NNSG3dResMdl *);
extern void NNSi_G3dAnmCalcNsBca(
    struct NNSG3dJntAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void func_0201c450(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void func_0201c51c(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void func_0201c924(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void func_0201c9f0(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void func_0201ca50(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void func_0201cc5c(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void func_0201ccec(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void func_0201cd34(
    struct NNSG3dVisAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);

NNSG3dFuncAnmBlendMat NNS_G3dFuncBlendMatDefault = NNSi_G3dAnmBlendMat;
NNSG3dFuncAnmBlendJnt NNS_G3dFuncBlendJntDefault = NNSi_G3dAnmBlendJnt;
NNSG3dFuncAnmBlendVis NNS_G3dFuncBlendVisDefault = NNSi_G3dAnmBlendVis;

NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBmaDefault = func_0201c51c;
NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBtpDefault = func_0201cc5c;
NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBtaDefault = func_0201c9f0;
NNSG3dFuncAnmJnt NNS_G3dFuncAnmJntNsBcaDefault = NNSi_G3dAnmCalcNsBca;
NNSG3dFuncAnmVis NNS_G3dFuncAnmVisNsBvaDefault = func_0201cd34;

u32 NNS_G3dAnmFmtNum = 5;

NNSG3dAnmObjInitFunc NNS_G3dAnmObjInitFuncArray[5] = {
    {'M', 0, 'MA', func_0201c450},
    {'M', 0, 'TP', func_0201ca50},
    {'M', 0, 'TA', func_0201c924},
    {'V', 0, 'VA', func_0201ccec},
    {'J', 0, 'CA', NNSi_G3dAnmObjInitNsBca}
};
