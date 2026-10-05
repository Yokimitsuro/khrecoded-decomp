#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

typedef struct CollisionEdge {
    VecFx32 vertex;
    VecFx32 direction;
    VecFx32 normal;
    u8 pad_24[0xc];
} CollisionEdge;

typedef struct CollisionPolygon {
    CollisionEdge edges[4];
    u8 edgeCount;
    u8 pad_c1[3];
    VecFx32 normal;
} CollisionPolygon;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

#define FX_ABS(value) ((value) < 0 ? -(value) : (value))

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern fx32 FX_Sqrt(fx32 value);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern s64 _ll_sdiv(s64 numerator, s64 denominator);
extern s64 _s32_div_f(s32 numerator, s32 denominator);
extern fx32 ScaleDotProductFraction(const VecFx32 *a, fx32 scale, const VecFx32 *b);
extern fx32 ComputeDirectionalExtent(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern BOOL UpdateSignedPenetrationDepth(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern BOOL UpdatePenetrationDepth(fx32 extent, fx32 distance, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern void WritePenetrationContact(const PenetrationResult *result, void *contact, u32 flags);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void DivideVecByLength(VecFx32 *vec, fx32 divisor);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL NormalizeUnlessDefault(VecFx32 *vec);
extern BOOL NormalizeIfShort(VecFx32 *vec);
extern void NegateVecFx32(VecFx32 *vec);
extern VecFx32 AverageVecs(s32 count, ...);
extern BOOL IsCrossNearZero(const VecFx32 *a, const VecFx32 *b, VecFx32 *out, BOOL vertical);
extern VecFx32 GetNormalizedAxisRejectionMasked(const VecFx32 *vec, const VecFx32 *axis, BOOL vertical);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline s32 Remainder(s32 numerator, s32 denominator)
{
    return (s32)(_s32_div_f(numerator, denominator) >> 32);
}

static inline fx32 CylinderRadius(const CollisionCylinder *cylinder)
{
    return cylinder->radius;
}

static inline Vec2Fx32 MakeVec2(fx32 x, fx32 y)
{
    Vec2Fx32 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

static inline PenetrationResult MakeEmptyResult(void)
{
    PenetrationResult result;
    result.depth = 0x7FFFFFFF;
    return result;
}

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    VEC_Subtract(a, b, &diff);
    return diff;
}

static inline VecFx32 SubtractVecValue(const VecFx32 *a, VecFx32 b)
{
    VecFx32 diff;
    VEC_Subtract(a, &b, &diff);
    return diff;
}

static inline VecFx32 HalveVec(VecFx32 vec)
{
    vec.x >>= 1;
    vec.y >>= 1;
    vec.z >>= 1;
    return vec;
}

static inline VecFx32 NegateVec(VecFx32 vec)
{
    NegateVecFx32(&vec);
    return vec;
}

static inline VecFx32 ScaleVec(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace(&vec, scale);
    return vec;
}

static inline VecFx32 DivideVec(VecFx32 vec, fx32 divisor)
{
    DivideVecByLength(&vec, divisor);
    return vec;
}

static inline VecFx32 RejectAlongEdge(const VecFx32 *vec, const CollisionEdge *edge, fx32 amount)
{
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;
    scaledAxis = edge->direction;
    ScaleVecFx32InPlace(&scaledAxis, amount);
    projection = scaledAxis;
    VEC_Subtract(vec, &projection, &rejection);
    return rejection;
}

static inline VecFx32 CrossVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    VEC_CrossProduct(a, b, &cross);
    return cross;
}

static inline VecFx32 MultAddVec(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 sum;
    VEC_MultAdd(scale, v, add, &sum);
    return sum;
}

static inline VecFx32 CrossConditional(const VecFx32 *a, const VecFx32 *b, BOOL vertical)
{
    VecFx32 cross;
    if (!vertical) {
        VEC_CrossProduct(a, b, &cross);
    } else {
        cross.x = -(fx32)(((fx64)a->z * b->y + 0x800) >> 12);
        cross.y = 0;
        cross.z = (fx32)(((fx64)a->x * b->y + 0x800) >> 12);
    }
    return cross;
}

static inline fx32 DotConditional(const VecFx32 *a, const VecFx32 *b, BOOL vertical)
{
    if (vertical) {
        return b->y > 0 ? a->y : -a->y;
    }
    return VEC_DotProduct(a, b);
}

BOOL TestCylinderAgainstPolygon(CylinderShapeRef *cylinderRef, CollisionPolygon **polygonRef, void *contact, u32 flags)
{
    VecFx32 center;
    VecFx32 halfSegment;
    VecFx32 axis;
    PenetrationResult result;
    VecFx32 normal;
    VecFx32 offset;
    VecFx32 facing;
    VecFx32 tangent;
    VecFx32 startOffset;
    VecFx32 endOffset;
    VecFx32 rejection[2];
    VecFx32 binormal;
    VecFx32 rimNormal;
    VecFx32 endpointOffset[2];
    VecFx32 toPrev;
    VecFx32 toNext;
    Vec2Fx32 local;
    Vec2Fx32 edgeLocal;
    fx32 rejectionDist[2];
    Vec2Fx32 rimLocal;
    fx32 endpointDist[2];
    u8 extreme[2];
    BOOL isCapsule;
    CollisionCylinder *cylinder;
    CollisionPolygon *polygon;
    BOOL polygonVertical;
    u8 i;
    fx32 extent;
    BOOL bothVertical;
    fx32 alignment;
    fx32 distance;
    BOOL isParallel;
    BOOL isPerpendicular;
    BOOL noEdgeContact;
    BOOL vertical;
    fx32 halfLength;
    u8 edgeCount;
    CollisionEdge *edge;

    cylinder = cylinderRef->cylinder;
    polygon = *polygonRef;
    isCapsule = cylinderRef->kind == 3;
    vertical = FALSE;
    if (cylinder->direction.x == 0 && cylinder->direction.z == 0) {
        vertical = TRUE;
    }
    polygonVertical = polygon->normal.x == 0 && polygon->normal.z == 0;
    bothVertical = vertical && polygonVertical;
    center = vertical ? MakeVec(cylinder->start.x, (cylinder->start.y + cylinder->end.y) / 2, cylinder->start.z)
                      : AverageVecs(2, &cylinder->start, &cylinder->end);
    halfSegment = vertical ? MakeVec(0, FX_ABS(cylinder->end.y - cylinder->start.y) / 2, 0) : HalveVec(SubtractVec(&cylinder->end, &cylinder->start));
    halfLength = cylinder->length / 2;
    axis = cylinder->direction;
    result = MakeEmptyResult();
    offset = SubtractVec(&center, &polygon->edges[0].vertex);

    if (isCapsule) {
        if (bothVertical) {
            extent = halfLength + cylinder->radius;
        } else {
            fx32 projection = VEC_DotProduct(&polygon->normal, &halfSegment);
            if (projection < 0) {
                projection = -projection;
            }
            extent = cylinder->radius + projection;
        }
    } else if (bothVertical) {
        extent = halfLength;
    } else {
        extent = ComputeDirectionalExtent(cylinderRef->cylinder, &axis, halfLength * 2, &polygon->normal);
    }
    if (!UpdateSignedPenetrationDepth(extent, VEC_DotProduct(&polygon->normal, &offset), &polygon->normal, 0, &result)) {
        return FALSE;
    }

    noEdgeContact = TRUE;
    edgeCount = polygon->edgeCount;
    if (bothVertical) {
        alignment = 0x1000;
    } else {
        alignment = VEC_DotProduct(&polygon->normal, &axis);
        if (alignment < 0) {
            alignment = -alignment;
        }
    }
    isParallel = alignment == 0x1000;
    isPerpendicular = alignment == 0;
    if ((bothVertical && (cylinder->direction.y >= 0) != (polygon->normal.y >= 0)) || VEC_DotProduct(&axis, &polygon->normal) < 0) {
        facing = NegateVec(axis);
    } else {
        facing = axis;
    }

    for (i = 0; i < edgeCount; i++) {
        edge = (CollisionEdge *)polygon + i;
        offset = SubtractVec(&center, &edge->vertex);
        if (bothVertical) {
            normal = polygon->edges[i].normal;
        } else if (IsCrossNearZero(&edge->direction, &facing, &normal, vertical)) {
            normal = RejectAlongEdge(&offset, &polygon->edges[i], VEC_DotProduct(&offset, &edge->direction));
            if (NormalizeUnlessDefault(&normal)) {
                continue;
            }
            if (VEC_DotProduct(&normal, &edge->normal) < 0) {
                continue;
            }
        } else {
            VEC_Normalize(&normal, &normal);
        }
        extent = cylinder->radius;
        if (!UpdatePenetrationDepth(extent, distance = VEC_DotProduct(&offset, &normal), &normal, 0, &result)) {
            return FALSE;
        }
        if (distance > 0 || isPerpendicular) {
            fx32 along;
            noEdgeContact = FALSE;
            tangent = CrossConditional(&normal, &facing, vertical);
            local = MakeVec2(vertical ? (facing.y > 0 ? offset.y : -offset.y) : VEC_DotProduct(&offset, &facing), VEC_DotProduct(&offset, &tangent));
            edgeLocal = MakeVec2(bothVertical ? 0 : VEC_DotProduct(&edge->direction, &facing),
                                 bothVertical ? 0x1000 : VEC_DotProduct(&edge->direction, &tangent));
            along = local.x - (bothVertical ? 0 : (fx32)_ll_sdiv((s64)local.y * edgeLocal.x, edgeLocal.y));
            if (along < 0) {
                along = -along;
            }
            if (along > halfLength) {
                u8 nearest;
                startOffset = SubtractVec(&cylinder->start, &((CollisionEdge *)polygon + i)->vertex);
                endOffset = SubtractVec(&cylinder->end, &((CollisionEdge *)polygon + i)->vertex);
                rejection[0] = RejectAlongEdge(&startOffset, &polygon->edges[i], VEC_DotProduct(&startOffset, &((CollisionEdge *)polygon + i)->direction));
                rejection[1] = RejectAlongEdge(&endOffset, &polygon->edges[i], VEC_DotProduct(&endOffset, &((CollisionEdge *)polygon + i)->direction));
                rejectionDist[0] = VEC_DotProduct(&rejection[0], &rejection[0]);
                rejectionDist[1] = VEC_DotProduct(&rejection[1], &rejection[1]);
                nearest = rejectionDist[0] >= rejectionDist[1];
                if (VEC_DotProduct(&rejection[nearest], &edge->normal) >= 0) {
                    if (isCapsule) {
                        fx32 length = rejectionDist[nearest] = FX_Sqrt(rejectionDist[nearest]);
                        if (length < 16) {
                            normal = polygon->edges[i].normal;
                        } else {
                            normal = DivideVec(rejection[nearest], length);
                            VEC_Normalize(&normal, &normal);
                        }
                        extent = cylinder->radius;
                        if (!UpdatePenetrationDepth(extent, VEC_DotProduct(&normal, &rejection[nearest]), &normal, 1, &result)) {
                            return FALSE;
                        }
                    } else if (!isParallel && VEC_DotProduct(&axis, &edge->direction) != 0) {
                        fx32 cosine;
                        const VecFx32 *cross = &CrossVec(&normal, &polygon->edges[i].direction);
                        binormal = *cross;
                        rimLocal = MakeVec2(VEC_DotProduct(&rejection[nearest], &binormal), VEC_DotProduct(&rejection[nearest], &normal));
                        cosine = AbsDotProduct(&polygon->edges[i].direction, &axis);
                        rimNormal = ScaleVec(*cross, rimLocal.x);
                        rimNormal = MultAddVec((fx32)(((fx64)rimLocal.y * cosine + 0x800) >> 12), &normal, &rimNormal);
                        NormalizeIfShort(&rimNormal);
                        if (!UpdatePenetrationDepth(ScaleDotProductFraction(&axis, cylinder->radius, &rimNormal), VEC_DotProduct(&rimNormal, &rejection[nearest]), &rimNormal, 1, &result)) {
                            return FALSE;
                        }
                    }
                }
            }
        }
    }

    if (!isCapsule) {
        fx32 minProjection = 0x7FFFFFFF;
        fx32 maxProjection = 0x80000000;
        u8 j;
        for (j = 0; j < (u32)edgeCount; j++) {
            fx32 projection = VEC_DotProduct(&polygon->edges[j].vertex, &axis);
            if (minProjection > projection) {
                extreme[0] = j;
                minProjection = projection;
            }
            if (maxProjection < projection) {
                maxProjection = projection;
                extreme[1] = j;
            }
        }
        for (j = 0; j < 2; j++) {
            normal = j == 0 ? NegateVec(axis) : axis;
            offset = SubtractVec(&center, &polygon->edges[extreme[j]].vertex);
            if (!UpdatePenetrationDepth(halfLength, VEC_DotProduct(&normal, &offset), &normal, 0, &result)) {
                return FALSE;
            }
        }
    }

    if (!noEdgeContact) {
        u8 prev = edgeCount - 1;
        u8 k;
        for (k = 0; k < edgeCount; k++, prev = Remainder(prev + 1, edgeCount)) {
            fx32 along;
            fx32 prevSide;
            fx32 nextSide;
            offset = SubtractVec(&center, &polygon->edges[k].vertex);
            along = VEC_DotProduct(&offset, &axis);
            if (FX_ABS(along) < halfLength) {
                normal = GetNormalizedAxisRejectionMasked(&offset, &axis, vertical);
            } else if (along != 0) {
                u8 nearest;
                if (!isCapsule) {
                    continue;
                }
                endpointOffset[0] = SubtractVec(&cylinder->start, &polygon->edges[k].vertex);
                endpointOffset[1] = SubtractVec(&cylinder->end, &polygon->edges[k].vertex);
                endpointDist[0] = VEC_DotProduct(&endpointOffset[0], &endpointOffset[0]);
                endpointDist[1] = VEC_DotProduct(&endpointOffset[1], &endpointOffset[1]);
                nearest = endpointDist[0] >= endpointDist[1];
                if (endpointDist[nearest] <= 0) {
                    continue;
                }
                normal = DivideVec(endpointOffset[nearest], FX_Sqrt(endpointDist[nearest]));
                VEC_Normalize(&normal, &normal);
                offset = endpointOffset[nearest];
            }
            toPrev = SubtractVec(&polygon->edges[prev].vertex, &polygon->edges[k].vertex);
            toNext = SubtractVec(&polygon->edges[Remainder(k + 1, edgeCount)].vertex, &polygon->edges[k].vertex);
            prevSide = VEC_DotProduct(&toPrev, &normal);
            nextSide = VEC_DotProduct(&toNext, &normal);
            if (prevSide <= 0 && nextSide <= 0) {
                if (!UpdatePenetrationDepth(CylinderRadius(cylinder), VEC_DotProduct(&normal, &offset), &normal, 1, &result)) {
                    return FALSE;
                }
            }
        }
    }

    WritePenetrationContact(&result, contact, flags);
    return TRUE;
}
