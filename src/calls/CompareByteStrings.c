int CompareByteStrings(unsigned char *leftBytes, unsigned char *rightBytes, int length) {
    while (length != 0) {
        if (*leftBytes++ != *rightBytes++) {
            return (leftBytes[-1] < rightBytes[-1]) ? -1 : 1;
        }
        length--;
    }
    return 0;
}
