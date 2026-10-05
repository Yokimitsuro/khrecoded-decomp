char *strchr(char *string, int character)
{
    unsigned char target = (unsigned char)character;
    unsigned char current;

    current = *string++;
    while (current != 0) {
        if (current == target) {
            return string - 1;
        }
        current = *string++;
    }
    if (target != 0) {
        return 0;
    }
    return string - 1;
}
