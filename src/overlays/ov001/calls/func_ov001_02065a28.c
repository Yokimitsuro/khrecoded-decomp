extern int ScriptVm_ReadOperandInt();
extern int SaveCurrentSpawnPoint();

int func_ov001_02065a28(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    SaveCurrentSpawnPoint();
    return 1;
}
