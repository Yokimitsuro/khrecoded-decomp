extern char data_02059784;

void func_020101a0(unsigned int mask) {
    while (*(volatile unsigned short *)(&data_02059784 + 0x3a) & mask) {
    }
}
