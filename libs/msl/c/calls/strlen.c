int strlen(const unsigned char *text)
{
    int length = -1;
    unsigned char character;

    do {
        character = *text++;
        length++;
    } while (character != 0);
    return length;
}