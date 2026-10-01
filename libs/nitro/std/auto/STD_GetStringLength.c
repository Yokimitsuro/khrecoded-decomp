int STD_GetStringLength(const char *string)
{
    int length;
    unsigned long *words;
    unsigned long zeroBytes;

    for (length = 0; ((unsigned long)(string + length) & 3) != 0; length++) {
        if (!string[length])
            return length;
    }

    words = (unsigned long *)(string + length);
    for (;; length += 4) {
        zeroBytes = (*words & 0x7f7f7f7f) + 0x7f7f7f7f;
        zeroBytes = ~(zeroBytes | *words | 0x7f7f7f7f);

        if (zeroBytes != 0)
            break;

        words++;
    }

    while (string[length])
        length++;

    return length;
}
