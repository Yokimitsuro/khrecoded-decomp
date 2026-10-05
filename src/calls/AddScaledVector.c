typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

void AddScaledVector(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector)
{
    resultVector->x = baseVector->x + (fx32)(((fx64)scale * scaledVector->x) >> 27);
    resultVector->y = baseVector->y + (fx32)(((fx64)scale * scaledVector->y) >> 27);
    resultVector->z = baseVector->z + (fx32)(((fx64)scale * scaledVector->z) >> 27);
}
