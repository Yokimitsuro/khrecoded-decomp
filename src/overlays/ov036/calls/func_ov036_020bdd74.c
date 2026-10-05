extern int ScriptVm_ReadOperandInt();
extern int ToggleActorSlotFlip();

int func_ov036_020bdd74(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    ToggleActorSlotFlip();
    return 1;
}
