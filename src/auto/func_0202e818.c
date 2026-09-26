int func_0202e818(unsigned char *obj) {
    if (obj == 0) return 0;
    if (!(*(unsigned short *)(obj + 4) == 0xfeff
          && *(unsigned short *)(obj + 0xc) == 0x10
          && *(unsigned short *)(obj + 0xe) == 1)) {
        return 0;
    }
    {
        unsigned char *p = obj + *(int *)(obj + 0x10);
        return p[8] != 0 ? 0 : p[9];
    }
}
