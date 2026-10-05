#pragma thumb on
extern void NNS_G3dResDefaultRelease(unsigned int *h, int b, int c, int d);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern int data_02060840[];
int DeferredDraw_Release(int param_1, int param_2, int param_3, int param_4) {
    if ((unsigned int *)data_02060840[1] != 0) {
        NNS_G3dResDefaultRelease((unsigned int *)data_02060840[1], param_2, param_3, param_4);
        NNSi_FndFreeFromDefaultHeap((void *)data_02060840[1]);
        data_02060840[1] = 0;
        data_02060840[0] = 0;
    }
    return 1;
}
