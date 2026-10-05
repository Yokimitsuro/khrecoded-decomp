extern void NNS_G3dFreeAnmObj(void *allocator, void *anmObj);
extern void ReleaseSharedRecordSlot(int a);
extern void ReleaseResourceSlot(void);
extern void NNSi_FndFreeFromDefaultHeap(int a);
extern void *NNSi_FndGetAllocatorForDefaultHeap(int a);

void func_0202eb08(int *p) {
    int i, j;
    int last = 0;
    for (i = 4; i >= 0; i--) {
        for (j = ((short *)p)[i] - 1; j >= 0; j--) {
            NNS_G3dFreeAnmObj(NNSi_FndGetAllocatorForDefaultHeap(0), (void *)((int *)p[i + 4])[j]);
        }
        if (p[i + 4]) last = p[i + 4];
    }
    if (last) NNSi_FndFreeFromDefaultHeap(last);
    if (p[3]) {
        ReleaseResourceSlot();
        ReleaseSharedRecordSlot(p[3]);
    }
    p[3] = 0;
}
