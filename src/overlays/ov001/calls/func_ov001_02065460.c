extern int ScriptVm_ReadOperandInt();
extern int func_ov001_02063a58();

int func_ov001_02065460(int arg0) {
    signed char x = ScriptVm_ReadOperandInt(arg0);
    func_ov001_02063a58(x);
    return 1;
}
