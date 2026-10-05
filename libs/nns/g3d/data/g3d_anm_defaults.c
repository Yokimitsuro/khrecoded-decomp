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
extern void AnmObj_InitMatTable(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void NNSi_G3dAnmCalcNsBma(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void AnmObj_InitVisTable(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void NNSi_G3dAnmCalcNsBta(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void NNSi_G3dAnmObjInitNsBtp(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void NNSi_G3dAnmCalcNsBtp(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void NNSi_G3dAnmObjInitNsBva(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void NNSi_G3dAnmCalcNsBva(
    struct NNSG3dVisAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);

NNSG3dFuncAnmBlendMat NNS_G3dFuncBlendMatDefault = NNSi_G3dAnmBlendMat;
NNSG3dFuncAnmBlendJnt NNS_G3dFuncBlendJntDefault = NNSi_G3dAnmBlendJnt;
NNSG3dFuncAnmBlendVis NNS_G3dFuncBlendVisDefault = NNSi_G3dAnmBlendVis;

NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBmaDefault = NNSi_G3dAnmCalcNsBma;
NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBtpDefault = NNSi_G3dAnmCalcNsBtp;
NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBtaDefault = NNSi_G3dAnmCalcNsBta;
NNSG3dFuncAnmJnt NNS_G3dFuncAnmJntNsBcaDefault = NNSi_G3dAnmCalcNsBca;
NNSG3dFuncAnmVis NNS_G3dFuncAnmVisNsBvaDefault = NNSi_G3dAnmCalcNsBva;

u32 NNS_G3dAnmFmtNum = 5;

NNSG3dAnmObjInitFunc NNS_G3dAnmObjInitFuncArray[5] = {
    {'M', 0, 'MA', AnmObj_InitMatTable},
    {'M', 0, 'TP', NNSi_G3dAnmObjInitNsBtp},
    {'M', 0, 'TA', AnmObj_InitVisTable},
    {'V', 0, 'VA', NNSi_G3dAnmObjInitNsBva},
    {'J', 0, 'CA', NNSi_G3dAnmObjInitNsBca}
};
