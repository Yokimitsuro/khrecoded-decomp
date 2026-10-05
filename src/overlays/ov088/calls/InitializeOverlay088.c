extern void ConfigureOverlay088Display(void);
extern void LoadOverlay088Graphics(void *context);
extern void ApplyOverlay088GridStates(void *context);
extern void func_ov088_020bed2c(void *context);
int InitializeOverlay088(void *context) {
    ConfigureOverlay088Display();
    LoadOverlay088Graphics(context);
    ApplyOverlay088GridStates(context);
    func_ov088_020bed2c(context);
    return 1;
}
