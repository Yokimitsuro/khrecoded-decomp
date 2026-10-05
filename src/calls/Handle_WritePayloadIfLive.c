struct V3 {
    int x;
    int y;
    int z;
};

extern char *data_0206084c;

void Handle_WritePayloadIfLive(unsigned int handle, struct V3 *src) {
    char *rec = data_0206084c + 738584 + (handle >> 24) * 32;
    if (*(unsigned short *)(rec + 0x14) == 0) {
        return;
    }
    if (*(unsigned int *)(rec + 0x18) == (handle & 0xffffff)) {
        *(struct V3 *)(rec + 8) = *src;
    }
}
