extern int data_ov039_020bea20;

void PopStackEntry(void)
{
    int base = data_ov039_020bea20;
    int *count = (int *)(base + 0xcad4);
    int index = (*count)--;

    *(int *)(base + index * 4 + 0xcad8) = 0;
}
