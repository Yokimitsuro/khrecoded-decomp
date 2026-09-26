extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *data_ov027_020ba3e0;
extern void func_ov027_020b9f90(void);

void (*func_ov027_020b9f74(void))(void)
{
    data_ov027_020ba3e0 = NNSi_FndGetCurrentRootHeap();
    return func_ov027_020b9f90;
}
