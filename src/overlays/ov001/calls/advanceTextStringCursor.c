int advanceTextStringCursor(int textBytes, int *byteCursor) {
    int cursor = *byteCursor;

    while (*(signed char *)(textBytes + cursor) != 0) {
        int leadByte = ((signed char *)textBytes)[cursor];
        if (leadByte >= 1 && leadByte < 0x20) {
            *byteCursor += 1;
            if (leadByte == 3) {
                *byteCursor += 1;
                return 1;
            }
        } else if (leadByte >= 0x20 && leadByte < 0x80) {
            *byteCursor += 1;
        } else {
            if ((leadByte & 0xe0) == 0xc0) {
                *byteCursor += 2;
            } else if ((leadByte & 0xf0) == 0xe0) {
                *byteCursor += 3;
            }
        }
        cursor = *byteCursor;
    }
    return 0;
}
