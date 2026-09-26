extern void MI_CpuFill8(void *dest, unsigned char val, unsigned int size);

void func_020127fc(void *dest)
{
    MI_CpuFill8(dest, 0, 0x24);
}
