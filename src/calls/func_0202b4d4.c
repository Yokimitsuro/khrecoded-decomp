extern void Cmd_DispatchWithFlag();
extern void Gfx_DispatchByPairKeyA();
extern void Gfx_DispatchByPairKeyA_0202b384();
extern void func_0202b490();
void func_0202b4d4(int param_1, unsigned short *param_2, int param_3, int *param_4, int param_5, int param_6)
{
    switch (param_2[3]) {
    case 0:
        Cmd_DispatchWithFlag(param_1, param_2, param_5, param_6);
        break;
    case 1:
        Gfx_DispatchByPairKeyA(param_1, param_2, param_5, param_6);
        break;
    case 2:
        Gfx_DispatchByPairKeyA_0202b384(param_1, param_2, param_5, param_6);
        break;
    }
    func_0202b490(param_1, (int)param_2, param_3, param_4);
}
