int func_ov022_020a9f78(int p)
{
    int i = *(int *)(p + 0x90);
    return *(int *)(p + i * 4 + 0x88);
}
