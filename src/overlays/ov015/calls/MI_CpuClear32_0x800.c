extern void func_01ff86fc(unsigned int value, void *destination, unsigned int size);

void MI_CpuClear32_0x800(void *destination) {
    func_01ff86fc(0, destination, 0x800);
}
