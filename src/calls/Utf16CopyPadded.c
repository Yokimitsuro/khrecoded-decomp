unsigned short *Utf16CopyPadded(unsigned short *destination, unsigned short *source, int unitCount) {
    unsigned short *writeCursor = destination;
    if (unitCount == 0) return destination;
    do {
        unsigned short *writtenUnit = writeCursor;
        *writeCursor++ = *source++;
        if (*(volatile unsigned short *)writtenUnit == 0) {
            unitCount--;
            if (unitCount != 0) {
                do {
                    *writeCursor++ = 0;
                    unitCount--;
                } while (unitCount != 0);
            }
            return destination;
        }
        unitCount--;
    } while (unitCount != 0);
    return destination;
}
