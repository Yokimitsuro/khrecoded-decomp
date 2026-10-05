extern void func_01ffb2f8(void *p, unsigned short i, int z);
extern void NNS_G3dRenderObjRemoveAnmObj(void *base, int item);
extern void selectJointAnimationBlend(void *p, unsigned short i, int a, short m);

void RebindEmitterSlots(int r0, int r1) {
    int i;
    for (i = 0; i < 5; i++) {
        if (((int *)r0)[i + 3] != 0) {
            NNS_G3dRenderObjRemoveAnmObj((void *)(r0 + 0x20), ((int *)r0)[i + 3]);
            ((int *)r0)[i + 3] = 0;
        }
        selectJointAnimationBlend((void *)r0, i, r0 + 268, (short)r1);
        func_01ffb2f8((void *)r0, i, 0);
    }
}
