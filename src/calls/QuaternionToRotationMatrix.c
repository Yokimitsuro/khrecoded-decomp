typedef int fx32;

typedef struct QuatFx32 {
    fx32 w_component;
    fx32 x_component;
    fx32 y_component;
    fx32 z_component;
} QuatFx32;

typedef struct MtxFx33 {
    fx32 matrix_elements[3][3];
} MtxFx33;

static inline fx32 Fx32Multiply(fx32 left_operand, fx32 right_operand)
{
    return (fx32)(((long long)left_operand * right_operand + 0x800) >> 12);
}

void QuaternionToRotationMatrix(MtxFx33 *matrix, const QuatFx32 *quaternion)
{
    fx32 twice_x = quaternion->x_component * 2;
    fx32 twice_y = quaternion->y_component * 2;
    fx32 twice_z = quaternion->z_component * 2;

    fx32 wx = Fx32Multiply(twice_x, quaternion->w_component);
    fx32 wy = Fx32Multiply(twice_y, quaternion->w_component);
    fx32 wz = Fx32Multiply(twice_z, quaternion->w_component);
    fx32 xx = Fx32Multiply(twice_x, quaternion->x_component);
    fx32 xy = Fx32Multiply(twice_y, quaternion->x_component);
    fx32 xz = Fx32Multiply(twice_z, quaternion->x_component);
    fx32 yy = Fx32Multiply(twice_y, quaternion->y_component);
    fx32 yz = Fx32Multiply(twice_z, quaternion->y_component);
    fx32 zz = Fx32Multiply(twice_z, quaternion->z_component);

    matrix->matrix_elements[0][0] = 0x1000 - (yy + zz);
    matrix->matrix_elements[1][0] = xy - wz;
    matrix->matrix_elements[2][0] = xz + wy;

    matrix->matrix_elements[0][1] = xy + wz;
    matrix->matrix_elements[1][1] = 0x1000 - (xx + zz);
    matrix->matrix_elements[2][1] = yz - wx;

    matrix->matrix_elements[0][2] = xz - wy;
    matrix->matrix_elements[1][2] = yz + wx;
    matrix->matrix_elements[2][2] = 0x1000 - (xx + yy);
}
