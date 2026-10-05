extern void PXI_Init_0202a64c(int arg);

extern int data_ov001_0209ead0;

void ReleaseServiceInstance(void) {
    if (data_ov001_0209ead0 == -1) return;
    PXI_Init_0202a64c(data_ov001_0209ead0);
    data_ov001_0209ead0 = -1;
}
