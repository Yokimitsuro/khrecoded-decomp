extern int ScriptVm_ReadOperandInt();
extern int CommitSideResult();

int func_ov007_020a0670(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    CommitSideResult();
    return 1;
}
