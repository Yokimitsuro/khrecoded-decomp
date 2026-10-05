extern int  SetDefaultHeap(int arena);
extern void func_0202a3bc(int node);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void NNSi_FndFreeToExpHeap(void *obj, void *heap);
extern int  data_020603c8[];
extern int  data_02060394[];

int func_0202a5c8(int *param_1)
{
    int uVar3;
    void (*cb)(void);
    int iVar2;

    iVar2 = SetDefaultHeap(param_1[7]);
    uVar3 = data_020603c8[1];
    data_020603c8[1] = (int)param_1;
    cb = (void (*)(void))param_1[6];
    if (cb != 0) {
        cb();
    }
    *param_1 = 0;
    data_020603c8[1] = uVar3;
    func_0202a3bc((int)param_1);
    uVar3 = param_1[3];
    if (param_1[8] != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)param_1[8]);
    }
    NNSi_FndFreeToExpHeap(param_1, (void *)data_02060394[0]);
    SetDefaultHeap(iVar2);
    return uVar3;
}
