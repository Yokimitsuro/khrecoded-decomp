char *strcat(char *destination, const char *source)
{
    unsigned char *output = (unsigned char *)destination;
    const unsigned char *input = (const unsigned char *)source;

    while (*output++ != 0) {
    }
    output--;
    while ((*output++ = *input++) != 0) {
    }
    return destination;
}
