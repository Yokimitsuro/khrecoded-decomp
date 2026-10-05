typedef struct { int identity_matrix[3][3]; } MtxFx33;

extern void MTX_Identity33_(MtxFx33 *mtx);
extern void GXi_FlushCommandList(void);
extern void NNS_G3dGeBufferOP_N(unsigned int cmd, const void *src, unsigned int words);
extern void NNS_G3dGlbFlushP(void);

typedef struct {
    char pad_00[0xb8];
    int translation_x;
    int translation_y;
    int translation_z;
    int scale_x;
    int scale_y;
    int scale_z;
    char pad_d0[0x4];
    unsigned int dirty_flags;
} GraphicsState;

extern GraphicsState NNS_G3dGlb;
extern MtxFx33  NNS_G3dGlb_prmBaseRot;

void ResetGraphicsTransform(void) {
    MtxFx33 identity_matrix;
    int graphics_command;

    NNS_G3dGlb.scale_z = 0x1000;
    NNS_G3dGlb.scale_y = 0x1000;
    NNS_G3dGlb.scale_x = 0x1000;
    MTX_Identity33_(&identity_matrix);
    MTX_Identity33_(&NNS_G3dGlb_prmBaseRot);
    NNS_G3dGlb.translation_z = 0;
    NNS_G3dGlb.translation_y = 0;
    NNS_G3dGlb.translation_x = 0;
    NNS_G3dGlb.dirty_flags &= ~0xa4u;
    NNS_G3dGlbFlushP();
    graphics_command = 0x7fff;
    NNS_G3dGeBufferOP_N(0x20, &graphics_command, 1);
    GXi_FlushCommandList();
}
