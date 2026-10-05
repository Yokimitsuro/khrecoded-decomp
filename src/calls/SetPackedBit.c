void SetPackedBit(int *bitWords, int bitIndex) {
    int wordIndex = bitIndex / 32;
    bitIndex = 31 - (bitIndex & 0x1f);
    bitWords[wordIndex] |= 1U << bitIndex;
}
