extern int strlen(void *text);
extern int PXI_Init_02022af8(void *entry, void *name, int nameLength);

int findSharedResourceByName(unsigned char *table, void *name) {
    int entryIndex;
    unsigned char *entry;
    int nameLength;
    unsigned short entryCount;

    nameLength = strlen(name);
    entryCount = (unsigned short)(*(unsigned short *)(table + 2) & 0x1ff);
    entry = (table + 0x10) + (((unsigned int)((entryCount + 1) / 2) << 17) >> 15);
    entry += entryCount * 4;
    for (entryIndex = 0; entryIndex < entryCount; entryIndex++) {
        if (PXI_Init_02022af8(entry, name, nameLength) == 0) {
            return entryIndex;
        }
        entry += 8;
    }
    return -1;
}
