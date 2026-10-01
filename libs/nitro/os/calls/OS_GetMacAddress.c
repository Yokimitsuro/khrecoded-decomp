extern void MI_CpuCopy8(const void *source, void *destination, unsigned int size);

void OS_GetMacAddress(void *macAddress)
{
    MI_CpuCopy8((const void *)0x02fffcf4, macAddress, 6);
}