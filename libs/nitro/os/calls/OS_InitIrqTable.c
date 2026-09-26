/* OS_InitIrqTable: clears the two-word IRQ table at data_027e00a0. */

extern int data_027e00a0;

void OS_InitIrqTable(void) {
    *(int *)((int)&data_027e00a0 + 4) = 0;
    data_027e00a0 = 0;
}
