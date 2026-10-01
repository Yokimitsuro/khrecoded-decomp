extern void CARDi_RequestStreamCommand(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8);

void func_02026c80(int arg0, int arg1, int arg2)
{
    CARDi_RequestStreamCommand(arg1, arg0, arg2, 0, 0, 1, 8, 0xa, 2);
}
