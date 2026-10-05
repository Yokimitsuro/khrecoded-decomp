unsigned short *Utf16Copy(unsigned short *destination, unsigned short *source) {
    unsigned short *destinationCursor = destination, *destinationSlot;
    unsigned short copiedValue;
    do {
        destinationSlot = destinationCursor++;
        *destinationSlot = *source++;
        copiedValue = *(volatile unsigned short *)destinationSlot;
    } while (copiedValue != 0);
    return destination;
}
