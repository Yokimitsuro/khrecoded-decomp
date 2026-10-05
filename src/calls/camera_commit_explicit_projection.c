typedef struct { int x, y, z; } VecFx32;

typedef struct {
    char    _0[0xc];
    int     nearClip;
    int     farClip;
    VecFx32 target;
    VecFx32 pos;
    VecFx32 up;
} CamActor;

extern struct { char _p00[0xd4]; int flags; } NNS_G3dGlb;
extern char    NNS_G3dGlb_projMtx[];
extern VecFx32 NNS_G3dGlb_camPos;
extern VecFx32 NNS_G3dGlb_camUp;
extern VecFx32 NNS_G3dGlb_camTarget;
extern char    NNS_G3dGlb_cameraMtx[];

extern void MTX_OrthoW(int top, int bottom, int left, int right, int nearClip, int farClip, int scaleW, void *projectionOut);
extern void func_01ff9b70(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target, void *viewOut);

void camera_commit_explicit_projection(CamActor *camera, int projectionTop, int projectionBottom, int projectionLeft, int projectionRight)
{
    MTX_OrthoW(projectionTop, projectionBottom, projectionLeft, projectionRight, camera->nearClip, camera->farClip, 0x1000, NNS_G3dGlb_projMtx);
    NNS_G3dGlb.flags &= ~0x50;
    NNS_G3dGlb_camPos = camera->pos;
    NNS_G3dGlb_camUp = camera->up;
    NNS_G3dGlb_camTarget = camera->target;
    func_01ff9b70(&camera->pos, &camera->up, &camera->target, NNS_G3dGlb_cameraMtx);
    NNS_G3dGlb.flags &= ~0xe8;
}
