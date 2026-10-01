typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned short u16;
typedef unsigned long u32;
typedef s16 fx16;
typedef s32 fx32;
typedef s64 fx64;

#define FX32_SHIFT 12
#define FX32_ONE (1 << FX32_SHIFT)

typedef struct MtxFx44 {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

typedef struct NNSG3dMatAnmResult {
    u32 flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmTexImage;
    u32 prmTexPltt;
    fx32 scaleS;
    fx32 scaleT;
    fx16 sinR;
    fx16 cosR;
    fx32 transS;
    fx32 transT;
    u16 origWidth;
    u16 origHeight;
    fx32 magW;
    fx32 magH;
} NNSG3dMatAnmResult;

extern void FX_DivAsync(fx32 numerator, fx32 denominator);
extern fx32 FX_GetDivResult(void);

void texmtxCalc_flag_(MtxFx44 *matrix, const NNSG3dMatAnmResult *animation)
{
    fx32 ss_sin;
    fx32 ss_cos;
    fx32 st_sin;
    fx32 st_cos;
    fx32 width;
    fx32 height;

    width = (s32)animation->origWidth << FX32_SHIFT;
    height = (s32)animation->origHeight << FX32_SHIFT;
    FX_DivAsync(height, width);

    ss_sin = (fx32)((fx64)animation->scaleS * animation->sinR >> FX32_SHIFT);
    ss_cos = (fx32)((fx64)animation->scaleS * animation->cosR >> FX32_SHIFT);
    st_sin = (fx32)((fx64)animation->scaleT * animation->sinR >> FX32_SHIFT);
    st_cos = (fx32)((fx64)animation->scaleT * animation->cosR >> FX32_SHIFT);

    matrix->_00 = ss_cos;
    matrix->_11 = st_cos;

    matrix->_01 = -st_sin * FX_GetDivResult() >> FX32_SHIFT;
    FX_DivAsync(width, height);

    matrix->_30 = ((-ss_sin - ss_cos + animation->scaleS) * animation->origWidth << 3) -
                  (fx32)((fx64)animation->scaleS * animation->transS >> (FX32_SHIFT - 4)) *
                      animation->origWidth;

    matrix->_31 = ((st_sin - st_cos - animation->scaleT + FX32_ONE * 2) *
                   animation->origHeight << 3) +
                  (fx32)((fx64)animation->scaleT * animation->transT >> (FX32_SHIFT - 4)) *
                      animation->origHeight;

    matrix->_10 = ss_sin * FX_GetDivResult() >> FX32_SHIFT;
}