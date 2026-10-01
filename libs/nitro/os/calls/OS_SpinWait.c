typedef unsigned int u32;

extern void OS_SpinWaitCpuCycles(u32 cycles);

void OS_SpinWait(u32 cycles)
{
    cycles <<= 1;
    if (cycles > 16) {
        OS_SpinWaitCpuCycles(cycles - 16);
    }
}