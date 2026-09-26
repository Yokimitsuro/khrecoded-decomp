extern int data_020603c8[];
extern int data_020603d8[];

void func_0202a3bc(int param_1)
{
    unsigned int uVar3;
    int iVar2;
    int bkt;

    uVar3 = *(unsigned short *)(param_1 + 0x10);
    if (data_020603c8[3] == param_1) {
        data_020603c8[3] = *(int *)(param_1 + 0xc);
    }
    bkt = data_020603d8[uVar3];
    if (bkt == param_1) {
        iVar2 = *(int *)(param_1 + 0xc);
        if (iVar2 != 0 && *(unsigned short *)(iVar2 + 0x10) == uVar3) {
            data_020603d8[uVar3] = iVar2;
        } else {
            data_020603d8[uVar3] = 0;
        }
    }
    if (*(int *)(param_1 + 0xc) != 0) {
        *(int *)(*(int *)(param_1 + 0xc) + 8) = *(int *)(param_1 + 8);
    }
    if (*(int *)(param_1 + 8) != 0) {
        *(int *)(*(int *)(param_1 + 8) + 0xc) = *(int *)(param_1 + 0xc);
    }
}
