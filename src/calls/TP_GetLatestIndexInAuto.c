extern int data_02059784;

int TP_GetLatestIndexInAuto(void) {
    return *(unsigned short *)((int)&data_02059784 + 0x10);
}
