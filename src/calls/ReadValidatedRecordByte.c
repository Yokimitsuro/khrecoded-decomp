int ReadValidatedRecordByte(unsigned char *header) {
    if (header == 0) return 0;
    if (!(*(unsigned short *)(header + 4) == 0xfeff
          && *(unsigned short *)(header + 0xc) == 0x10
          && *(unsigned short *)(header + 0xe) == 1)) {
        return 0;
    }
    {
        unsigned char *record = header + *(int *)(header + 0x10);
        return record[8] != 0 ? 0 : record[9];
    }
}
