extern void MIi_CpuClear32(unsigned int value, void *destination, unsigned int size);

void MI_CpuClear32_0x800(void *destination) {
    MIi_CpuClear32(0, destination, 0x800);
}
