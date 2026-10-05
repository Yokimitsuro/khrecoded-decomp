typedef struct { int x, y, z; } VecFx32;

typedef struct {
    int     perspectiveParams[4];
    int     farClip;
    VecFx32 target;
    VecFx32 pos;
    VecFx32 up;
} CamActor;

extern struct {
    char    _p00[0xd4];
    int     flags;
    char    _pd8[0x218-0xd8];
    VecFx32 cachePos;
    VecFx32 cacheUp;
    VecFx32 cacheTarget;
} NNS_G3dGlb;

extern char NNS_G3dGlb_projMtx[];
extern char NNS_G3dGlb_cameraMtx[];

extern void Camera_BuildProjectionMtx(int fovySin, int fovyCos, int aspect, int nearClip, int farClip, int scaleW, void *projectionOut);
extern void func_01ff9b70(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target,
                          void *viewOut);

void camera_commit_projection(CamActor *camera)
{
    Camera_BuildProjectionMtx(camera->perspectiveParams[0], camera->perspectiveParams[1], camera->perspectiveParams[2],
                  camera->perspectiveParams[3], camera->farClip, 0x1000, NNS_G3dGlb_projMtx);
    NNS_G3dGlb.flags &= ~0x50;
    NNS_G3dGlb.cachePos = camera->pos;
    NNS_G3dGlb.cacheUp = camera->up;
    NNS_G3dGlb.cacheTarget = camera->target;
    func_01ff9b70(&camera->pos, &camera->up, &camera->target, NNS_G3dGlb_cameraMtx);
    NNS_G3dGlb.flags &= ~0xe8;
}
