int GetPackedBitMask(int *bitWords, int bitIndex) {
    int wordIndex = bitIndex / 32;
    bitIndex = 31 - (bitIndex & 0x1f);
    return bitWords[wordIndex] & (1U << bitIndex);
}
