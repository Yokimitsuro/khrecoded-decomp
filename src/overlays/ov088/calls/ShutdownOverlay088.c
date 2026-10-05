extern void func_ov088_020bebe8(void);
extern void ClearOverlay088Grid(void *context);
extern void func_ov088_020bedf0(void *context);
void ShutdownOverlay088(void *context) {
    func_ov088_020bebe8();
    ClearOverlay088Grid(context);
    func_ov088_020bedf0(context);
}
