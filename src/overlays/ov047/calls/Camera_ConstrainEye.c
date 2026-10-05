#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    u8 pad_00[0x14];
    VecFx32 position;
    VecFx32 lookAt;
    VecFx32 up;
} CameraView;

typedef struct CameraTrackingFlags {
    int unk_0 : 1;
    int turning : 1;
} CameraTrackingFlags;

typedef struct CameraTracking {
    BOOL active;
    int state;
    int heading;
    fx32 distance;
    int angle;
    fx32 height;
    fx32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    VecFx32 lookAt;
    VecFx32 target;
    VecFx32 prevLookAt;
    VecFx32 prevTarget;
    VecFx32 direction;
    VecFx32 prevDirection;
    VecFx32 unk_6C;
    fx32 prevHeight;
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
    fx32 savedUnk18;
    VecFx32 unk_A4;
    int unk_B0;
    int unk_B4;
    u16 unk_B8;
    u16 unk_BA;
    fx32 unk_BC;
    fx32 unk_C0;
    fx32 unk_C4;
    fx32 unk_C8;
    fx32 unk_CC;
    int unk_D0;
    int unk_D4;
    int unk_D8;
    int unk_DC;
    u8 pad_E0[0xc];
    int unk_EC;
    int unk_F0;
    int unk_F4;
    int turnTimer;
    fx32 turnSpeed;
    u8 pad_100[0x4];
    int unk_104;
    int unk_108;
    int unk_10C;
    int unk_110;
    u8 pad_114[0x6];
    u16 unk_11A;
    u8 pad_11C[0xc];
    int unk_128;
    CameraTrackingFlags trackFlags;
    int unk_130;
} CameraTracking;

typedef struct CameraBox {
    VecFx32 max;
    VecFx32 min;
} CameraBox;

typedef struct CameraManagerFlags {
    u32 unk_0 : 1;
} CameraManagerFlags;

typedef struct CameraManager {
    CameraView view;
    VecFx32 eye;
    VecFx32 unk_44;
    u8 pad_50[0x94];
    int mode;
    int prevMode;
    u8 pad_EC[0x4];
    u32 flags;
    int unk_F4;
    CameraBox bounds;
    u8 pad_110[0x18];
    CameraManagerFlags extraFlags;
    u8 pad_12C[0x10];
    CameraTracking tracking;
} CameraManager;


typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct CollisionShape {
    void *data;
    VecFx32 max;
    VecFx32 min;
    int kind;
} CollisionShape;

typedef struct ShapeHit {
    fx32 depth;
    VecFx32 normal;
    u8 pad_10[0x8];
} ShapeHit;

typedef struct FocusBody {
    u8 pad_00[0x28];
    fx32 radius;
} FocusBody;

typedef struct FxPair {
    fx32 x;
    fx32 y;
} FxPair;

typedef BOOL (*ShapeTestFn)(CollisionShape *self, CollisionShape *other, ShapeHit *hit, int flags);

extern ShapeTestFn gCollisionTestPairDispatch[][6];
extern const s16 data_02053900[];
extern const s16 data_02053580[];
extern const s16 data_02053b80[];
extern const s16 data_02053740[];
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 ComputeOneMinusSquareFraction(fx32 value);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void ScalePairInPlace(FxPair *pair, fx32 scale);
extern u32 GetBoundedEntryField(int index);
extern CollisionShape func_0203ad28(Sphere *storage, const VecFx32 *center, fx32 radius);

void Camera_ConstrainEye(CameraTracking *tracking, CameraManager *camera)
{
    ShapeHit hit;
    Sphere sphere;
    CollisionShape probe;
    VecFx32 nearCopy;
    VecFx32 farCopy;
    VecFx32 nearOffset;
    VecFx32 farOffset;
    CollisionShape shape;
    VecFx32 pushed;
    FxPair scaled;
    FxPair pair;
    fx32 distance = VEC_Distance(&tracking->lookAt, &tracking->target);
    fx32 limit;
    CollisionShape *other;
    BOOL result;

    if (distance < 0x80) {
        nearOffset = tracking->direction;
        ScaleVecFx32InPlace(&nearOffset, -0x80);
        nearCopy = nearOffset;
        VEC_Add(&nearCopy, &tracking->target, &tracking->lookAt);
    }
    if (distance < 0xc00) {
        farOffset = tracking->direction;
        ScaleVecFx32InPlace(&farOffset, -0xc00);
        farCopy = farOffset;
        VEC_Add(&farCopy, &tracking->target, &camera->eye);
        distance = 0xc00;
    } else {
        camera->eye = tracking->lookAt;
    }
    limit = camera->unk_F4 == 0 ? data_02053900[7] : data_02053580[0];
    if (tracking->direction.y > limit) {
        fx32 horizontal = ComputeOneMinusSquareFraction(limit);

        tracking->direction.y = limit;
        tracking->direction.x = -FX_Mul(data_02053580[tracking->angle >> 4], horizontal);
        tracking->direction.z = -FX_Mul(data_02053580[(0x400 - (tracking->angle >> 4)) & 0xfff], horizontal);
        VEC_MultAdd(-distance, &tracking->direction, &tracking->target, &camera->eye);
    } else {
        limit = -data_02053b80[0x1c];
        if (tracking->direction.y < limit) {
            int index = (u16)tracking->angle >> 4;
            fx32 negZ;

            pair.x = data_02053580[(0x400 - index) & 0xfff];
            pair.y = data_02053580[index];
            scaled = pair;
            ScalePairInPlace(&scaled, data_02053740[4]);
            negZ = -scaled.x;
            tracking->direction.x = -scaled.y;
            tracking->direction.y = limit;
            tracking->direction.z = negZ;
        }
    }
    other = (CollisionShape *)(GetBoundedEntryField(0) + 0x144);
    shape = func_0203ad28(&sphere, &camera->eye, 0xc00 - ((FocusBody *)other->data)->radius);
    probe = shape;
    if (probe.max.x >= other->min.x && probe.min.x <= other->max.x &&
        probe.max.z >= other->min.z && probe.min.z <= other->max.z &&
        probe.max.y >= other->min.y && probe.min.y <= other->max.y) {
        result = gCollisionTestPairDispatch[probe.kind][other->kind](&probe, other, &hit, 0);
    } else {
        result = FALSE;
    }
    if (result) {
        VEC_MultAdd(hit.depth, &hit.normal, &camera->eye, &pushed);
        camera->eye = pushed;
    }
    VEC_Add(&camera->eye, &tracking->direction, &camera->unk_44);
}

