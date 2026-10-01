int G3X_GetMtxStackLevelPV(int *level)
{
    if ((*(volatile unsigned int *)0x04000600 & 0x4000) != 0) {
        return -1;
    }
    *level = (*(volatile unsigned int *)0x04000600 & 0x1f00) >> 8;
    return 0;
}