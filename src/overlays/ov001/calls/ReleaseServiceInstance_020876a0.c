extern void ReleaseStageManager(int arg);

extern int data_ov001_0209f2e8;

void ReleaseServiceInstance_020876a0(void) {
    if (data_ov001_0209f2e8 == -1) return;
    ReleaseStageManager(data_ov001_0209f2e8);
    data_ov001_0209f2e8 = -1;
}
