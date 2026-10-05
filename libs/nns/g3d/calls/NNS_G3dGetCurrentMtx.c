typedef unsigned int u32;
typedef int fx32;
typedef volatile u32 REGType32v;

typedef enum GXMtxMode {
    GX_MTXMODE_PROJECTION = 0,
    GX_MTXMODE_POSITION_VECTOR = 2
} GXMtxMode;

#define offsetof(type, member) ((u32)&(((type *)0)->member))

typedef union {
    struct {
        fx32 _00, _01, _02, _03;
        fx32 _10, _11, _12, _13;
        fx32 _20, _21, _22, _23;
        fx32 _30, _31, _32, _33;
    };
    fx32 m[4][4];
    fx32 a[16];
} MtxFx44;

typedef union {
    struct {
        fx32 _00, _01, _02;
        fx32 _10, _11, _12;
        fx32 _20, _21, _22;
        fx32 _30, _31, _32;
    };
    fx32 m[4][3];
    fx32 a[12];
} MtxFx43;

typedef union {
    struct {
        fx32 _00, _01, _02;
        fx32 _10, _11, _12;
        fx32 _20, _21, _22;
    };
    fx32 m[3][3];
    fx32 a[9];
} MtxFx33;

int G3X_GetClipMtx(MtxFx44 *m);
int G3X_GetVectorMtx(MtxFx33 *m);
extern void G3_MtxMode(GXMtxMode mode);
extern void G3_PushMtx(void);
extern void G3_PopMtx(int num);
extern void G3_Identity(void);

static inline void G3_MtxMode(GXMtxMode mode)
{
    (*(REGType32v *)(0x04000000 + 0x440)) = (u32)(mode << 0);
}

static inline void G3_PushMtx(void)
{
    (*(REGType32v *)(0x04000000 + 0x444)) = 0;
}

static inline void G3_PopMtx(int num)
{
    (*(REGType32v *)(0x04000000 + 0x448)) = (u32)num;
}

static inline void G3_Identity(void)
{
    (*(REGType32v *)(0x04000000 + 0x454)) = 0;
}

extern void MTX_Copy44To43(const MtxFx44 *src, MtxFx43 *dst);
void MTX_Copy44To43_(register const MtxFx44 *src, register MtxFx43 *dst);

static inline void MTX_Copy44To43(const MtxFx44 *src, MtxFx43 *dst)
{
    MTX_Copy44To43_(src, dst);
}

void GXi_FlushCommandList(void);

void NNS_G3dGetCurrentMtx(MtxFx43 *m, MtxFx33 *n)
{
    GXi_FlushCommandList();

    G3_MtxMode(GX_MTXMODE_PROJECTION);
    G3_PushMtx();
    G3_Identity();

    if (m) {
        MtxFx44 tmp;
        while (G3X_GetClipMtx(&tmp)) {
        }
        MTX_Copy44To43(&tmp, m);
    }

    if (n) {
        while (G3X_GetVectorMtx(n)) {
        }
    }

    G3_PopMtx(1);
    G3_MtxMode(GX_MTXMODE_POSITION_VECTOR);
}
