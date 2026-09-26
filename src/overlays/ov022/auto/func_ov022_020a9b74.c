int func_ov022_020a9b74(int p)
{
    if (*(int *)(p + 0x20) == 0)
        return 0;
    if (*(int *)(p + 0x28) != 0)
        return 0x80;
    return 0x100;
}
