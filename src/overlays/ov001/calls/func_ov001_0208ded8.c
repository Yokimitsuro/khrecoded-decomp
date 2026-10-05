extern int func_02025df8(int ctx, void *arg);
extern int func_02025974(int ctx, int arg);
extern char *func_02036254(int index);

extern void NNS_G3dMdlSetMdlAlphaAll(int model, int alpha);
extern void NNS_G3dMdlSetMdlPolygonIDAll(int model, int polygonID);

typedef struct { int x, y, z; } Ov023Vec3;

int func_ov001_0208ded8(int ctx, int args) {
    char *node = func_02036254((unsigned short)func_02025974(ctx, func_02025df8(ctx, (void *)args)));
    Ov023Vec3 v;
    v.x = *(int *)(node + 0xb4);
    v.y = 0;
    v.z = *(int *)(node + 0xbc);
    *(Ov023Vec3 *)(node + 0xb4) = v;
    NNS_G3dMdlSetMdlAlphaAll(*(int *)(node + 0x7c), 8);
    NNS_G3dMdlSetMdlPolygonIDAll(*(int *)(node + 0x7c), 0x3f);
    return 1;
}
