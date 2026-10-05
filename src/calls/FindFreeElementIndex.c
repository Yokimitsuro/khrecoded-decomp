int FindFreeElementIndex(int base)
{
    int index;
    int result;

    result = -1;
    index = 0;

    do {
        if (*(int *)(base + index * 0x68 + 0x461c) == 0) {
            result = index;
            break;
        }
        index++;
    } while (index < 0x40);

    return result;
}
