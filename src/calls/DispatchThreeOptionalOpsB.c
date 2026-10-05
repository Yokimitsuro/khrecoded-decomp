extern void Bg_LoadPaletteForScreen();
extern void Gfx_EnqueueTableCmdAt14();
extern void Gfx_EnqueueTableCmdAtC();
void DispatchThreeOptionalOpsB(int param_1, int param_2, int param_3, int *param_4)
{
    if (param_4 != 0 && param_2 != 0)
        Bg_LoadPaletteForScreen(param_1, param_4, param_2, 0, *(int *)((char *)param_4 + 8));
    if (param_3 != 0)
        Gfx_EnqueueTableCmdAt14(param_1, param_3, 0, *(int *)(param_3 + 0x10));
    if (param_2 != 0)
        Gfx_EnqueueTableCmdAtC(param_1, param_2, 0, *(int *)(param_2 + 8));
}
