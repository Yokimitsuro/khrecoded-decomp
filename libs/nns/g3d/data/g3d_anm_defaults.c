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

extern BOOL func_020197a0(
    struct NNSG3dMatAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern BOOL func_0201987c(
    struct NNSG3dJntAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern BOOL func_02019c6c(
    struct NNSG3dVisAnmResult_ *,
    const NNSG3dAnmObj *,
    u32);
extern void func_0201ae18(NNSG3dAnmObj *, void *, const NNSG3dResMdl *);
extern void func_0201ae94(
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

NNSG3dFuncAnmBlendMat NNS_G3dFuncBlendMatDefault = func_020197a0;
NNSG3dFuncAnmBlendJnt NNS_G3dFuncBlendJntDefault = func_0201987c;
NNSG3dFuncAnmBlendVis NNS_G3dFuncBlendVisDefault = func_02019c6c;

NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBmaDefault = func_0201c51c;
NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBtpDefault = func_0201cc5c;
NNSG3dFuncAnmMat NNS_G3dFuncAnmMatNsBtaDefault = func_0201c9f0;
NNSG3dFuncAnmJnt NNS_G3dFuncAnmJntNsBcaDefault = func_0201ae94;
NNSG3dFuncAnmVis NNS_G3dFuncAnmVisNsBvaDefault = func_0201cd34;

u32 NNS_G3dAnmFmtNum = 5;

NNSG3dAnmObjInitFunc NNS_G3dAnmObjInitFuncArray[5] = {
    {'M', 0, 'MA', func_0201c450},
    {'M', 0, 'TP', func_0201ca50},
    {'M', 0, 'TA', func_0201c924},
    {'V', 0, 'VA', func_0201ccec},
    {'J', 0, 'CA', func_0201ae18}
};
