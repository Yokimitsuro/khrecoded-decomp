extern int ByteCode_ResolveOperand();
extern int LoadCameraParams();

int func_ov001_02065638(int arg0) {
    ByteCode_ResolveOperand(arg0);
    LoadCameraParams();
    return 1;
}
