extern void *func_ov039_020bc1ec(void);
extern void func_ov027_020b902c(void *context);
extern void ReleaseIfMarked(void *context);
void ClearOverlay088Grid(void *unusedContext) {
    func_ov027_020b902c(func_ov039_020bc1ec());
    ReleaseIfMarked(func_ov039_020bc1ec());
}
