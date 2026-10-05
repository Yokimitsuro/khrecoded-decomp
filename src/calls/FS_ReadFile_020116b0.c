extern void *WM_InitializeEx();

void *FS_ReadFile_020116b0(int a, void *b, void *c) {
    return WM_InitializeEx(a, b, c, 0);
}
