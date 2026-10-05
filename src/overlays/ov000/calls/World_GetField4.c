extern int *data_ov000_02063a04;

int World_GetField4(void)
{
    if (data_ov000_02063a04 != 0) {
        return data_ov000_02063a04[1];
    }
    return 2;
}
