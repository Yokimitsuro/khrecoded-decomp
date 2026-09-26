typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    char pad0000[0xd4];
    unsigned int dwViewFlags;
} CameraState;

extern VecFx32 data_0205a9dc;
extern CameraState data_0205a924;

void func_02019300(const VecFx32 *target) {
    if (target == 0) {
        return;
    }

    data_0205a9dc = *target;
    data_0205a924.dwViewFlags &= ~0xa4;
}
