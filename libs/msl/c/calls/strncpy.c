char *strncpy(char *destination, const char *source, unsigned int length)
{
    unsigned char *output = (unsigned char *)destination;
    const unsigned char *input = (const unsigned char *)source;
    unsigned char *written;

    if (length == 0) {
        return destination;
    }
    do {
        written = output;
        *output++ = *input++;
        if (*written == 0) {
            while (--length != 0) {
                *output++ = 0;
            }
            return destination;
        }
    } while (--length != 0);
    return destination;
}
