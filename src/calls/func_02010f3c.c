extern char data_020597fc[];

void func_02010f3c(int idx, int value) {
    *(int *)(*(int *)(data_020597fc + 4) + idx * 4 + 0x18) = value;
}
