typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    char pad0000[0xd4];
    unsigned int dwViewFlags;
} CameraState;

extern VecFx32 data_0205a9e8;
extern CameraState data_0205a924;

void func_02019330(const VecFx32 *target) {
    if (target == 0) {
        return;
    }

    data_0205a9e8 = *target;
    data_0205a924.dwViewFlags &= ~0xa4;
}
