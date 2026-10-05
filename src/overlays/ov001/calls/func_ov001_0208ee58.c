extern int ScriptVm_ReadOperandInt();
extern int FrameCameraOnActor();

int func_ov001_0208ee58(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    FrameCameraOnActor();
    return 1;
}
