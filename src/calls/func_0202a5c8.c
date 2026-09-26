extern int  func_0202a148(int arena);
extern void func_0202a3bc(int node);
extern void func_0202a1d8(void *p);
extern void func_0202a254(void *obj, void *heap);
extern int  data_020603c8[];
extern int  data_02060394[];

int func_0202a5c8(int *param_1)
{
    int uVar3;
    void (*cb)(void);
    int iVar2;

    iVar2 = func_0202a148(param_1[7]);
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
        func_0202a1d8((void *)param_1[8]);
    }
    func_0202a254(param_1, (void *)data_02060394[0]);
    func_0202a148(iVar2);
    return uVar3;
}
