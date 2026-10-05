extern void PXI_Init_0202a64c(int arg);

extern int data_ov001_0209eae8;

void ReleaseServiceInstance_020690ac(void) {
    if (data_ov001_0209eae8 == -1) return;
    PXI_Init_0202a64c(data_ov001_0209eae8);
    data_ov001_0209eae8 = -1;
}
