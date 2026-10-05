extern char data_02059784;

void TP_WaitBusy(unsigned int mask) {
    while (*(volatile unsigned short *)(&data_02059784 + 0x3a) & mask) {
    }
}
