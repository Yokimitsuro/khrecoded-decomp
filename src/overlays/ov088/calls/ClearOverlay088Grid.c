extern void *func_ov039_020bc1ec(void);
extern void DestroyAllContainerElements(void *context);
extern void ReleaseIfMarked(void *context);
void ClearOverlay088Grid(void *unusedContext) {
    DestroyAllContainerElements(func_ov039_020bc1ec());
    ReleaseIfMarked(func_ov039_020bc1ec());
}
