int IndexedRecord_GetFlag2(int recordBase, int recordIndex) {
    return (((unsigned int *)(recordBase + recordIndex * 0x8c))[0x7c / 4] << 0x1d) >> 0x1f;
}
