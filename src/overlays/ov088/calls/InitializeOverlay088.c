extern void ConfigureOverlay088Display(void);
extern void func_ov088_020beb0c(void *context);
extern void func_ov088_020bebfc(void *context);
extern void func_ov088_020bed2c(void *context);
int InitializeOverlay088(void *context) {
    ConfigureOverlay088Display();
    func_ov088_020beb0c(context);
    func_ov088_020bebfc(context);
    func_ov088_020bed2c(context);
    return 1;
}
