extern int data_ov039_020bea20;

int GetFieldCad0(void)
{
    int base = data_ov039_020bea20;

    if (base != 0) {
        return *(int *)(base + 0xcad0);
    }
    return 0;
}
