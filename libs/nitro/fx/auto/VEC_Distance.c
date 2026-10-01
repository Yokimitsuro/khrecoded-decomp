typedef signed int fx32;
typedef signed long long fx64;
typedef unsigned short u16;
typedef unsigned long long u64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

#define SQRT_CONTROL (*(volatile u16 *)0x040002b0)
#define SQRT_RESULT (*(volatile fx32 *)0x040002b4)
#define SQRT_PARAMETER (*(volatile u64 *)0x040002b8)

fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b)
{
    fx32 x = a->x - b->x;
    fx32 y = a->y - b->y;
    fx32 z = a->z - b->z;
    fx64 squaredDistance = (fx64)x * x;

    squaredDistance += (fx64)y * y;
    squaredDistance += (fx64)z * z;

    SQRT_CONTROL = 1;
    SQRT_PARAMETER = (u64)(squaredDistance * 4);
    while (SQRT_CONTROL & 0x8000) {
    }

    return (SQRT_RESULT + 1) >> 1;
}