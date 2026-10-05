typedef struct FixedPointQuaternion {
    int w;
    int x;
    int y;
    int z;
} FixedPointQuaternion;

static inline int truncateFixedPointProduct(long long product)
{
    return (int)product;
}

static inline int multiplyFixedPoint(int leftFactor, int rightFactor)
{
    return truncateFixedPointProduct(((long long)leftFactor * rightFactor + 0x800LL) >> 12);
}

void MultiplyFixedPointQuaternions(FixedPointQuaternion *resultQuaternion, const FixedPointQuaternion *leftQuaternion, const FixedPointQuaternion *rightQuaternion)
{
    FixedPointQuaternion product;

    product.w = multiplyFixedPoint(leftQuaternion->w, rightQuaternion->w) - multiplyFixedPoint(leftQuaternion->x, rightQuaternion->x)
        - multiplyFixedPoint(leftQuaternion->y, rightQuaternion->y) - multiplyFixedPoint(leftQuaternion->z, rightQuaternion->z);
    product.x = multiplyFixedPoint(leftQuaternion->y, rightQuaternion->z)
        + (multiplyFixedPoint(leftQuaternion->w, rightQuaternion->x) + multiplyFixedPoint(leftQuaternion->x, rightQuaternion->w))
        - multiplyFixedPoint(leftQuaternion->z, rightQuaternion->y);
    product.y = multiplyFixedPoint(leftQuaternion->z, rightQuaternion->x)
        + (multiplyFixedPoint(leftQuaternion->w, rightQuaternion->y) + multiplyFixedPoint(leftQuaternion->y, rightQuaternion->w))
        - multiplyFixedPoint(leftQuaternion->x, rightQuaternion->z);
    product.z = multiplyFixedPoint(leftQuaternion->x, rightQuaternion->y)
        + (multiplyFixedPoint(leftQuaternion->w, rightQuaternion->z) + multiplyFixedPoint(leftQuaternion->z, rightQuaternion->w))
        - multiplyFixedPoint(leftQuaternion->y, rightQuaternion->x);

    *resultQuaternion = product;
}
