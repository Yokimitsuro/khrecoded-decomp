typedef signed long fx32;
typedef signed long long fx64;
typedef signed long long fx64c;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

typedef struct MtxFx44 {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

typedef unsigned long u32;

typedef struct CameraProjectionState {
    u32 unk00;
    u32 cmd0;
    u32 projectionMode;
    MtxFx44 projection;
    MtxFx43 camera;
} CameraProjectionState;

extern CameraProjectionState data_0205fe40;

extern void MTX_MultVec43(const VecFx32 *src, const MtxFx43 *mtx, VecFx32 *dst);
extern void FX_InvAsync(fx32 value);
extern fx64c FX_GetDivResultFx64c(void);
extern void NNS_G3dGlbGetViewPort(int *x1, int *y1, int *x2, int *y2);

static inline fx32 FX_Mul32x64c(fx32 x, fx64c y)
{
    return (fx32)((y * (fx64)x + 0x80000000LL) >> 32);
}

static inline const MtxFx44 *GetProjectionMatrix(void)
{
    return &data_0205fe40.projection;
}

static inline const MtxFx43 *GetCameraMatrix(void)
{
    return &data_0205fe40.camera;
}

int func_02028c38(const VecFx32 *worldPosition, int *screenX, int *screenY)
{
    const MtxFx44 *projection;
    const MtxFx43 *camera;
    VecFx32 transformed;
    VecFx32 projected;
    fx32 w;
    fx64c inverseW;
    int left;
    int top;
    int right;
    int bottom;
    int width;
    int height;
    int result;

    projection = GetProjectionMatrix();
    camera = GetCameraMatrix();

    MTX_MultVec43(worldPosition, camera, &transformed);

    w = (fx32)(((fx64)transformed.x * projection->_03 +
                (fx64)transformed.y * projection->_13 +
                (fx64)transformed.z * projection->_23) >> 12);
    w += projection->_33;

    FX_InvAsync(w);

    projected.x = (fx32)(((fx64)transformed.x * projection->_00 +
                          (fx64)transformed.y * projection->_10 +
                          (fx64)transformed.z * projection->_20) >> 12);
    projected.x += projection->_30;

    projected.y = (fx32)(((fx64)transformed.x * projection->_01 +
                          (fx64)transformed.y * projection->_11 +
                          (fx64)transformed.z * projection->_21) >> 12);
    projected.y += projection->_31;

    inverseW = FX_GetDivResultFx64c();
    projected.x = (FX_Mul32x64c(projected.x, inverseW) + 0x1000) / 2;
    projected.y = (FX_Mul32x64c(projected.y, inverseW) + 0x1000) / 2;

    if (projected.x < 0 || projected.y < 0 ||
        projected.x > 0x1000 || projected.y > 0x1000) {
        result = -1;
    } else {
        result = 0;
    }

    NNS_G3dGlbGetViewPort(&left, &top, &right, &bottom);
    width = right - left;
    height = bottom - top;

    *screenX = left + ((projected.x * width + 0x800) >> 12);
    *screenY = 191 - top - ((projected.y * height + 0x800) >> 12);

    return result;
}
