typedef void (*func_02025420_cb)(void *ptr, unsigned int arg1, unsigned int arg2);

extern func_02025420_cb data_02060574;

void func_0202d218(unsigned char *ptr) {
    data_02060574(ptr + *(int *)(ptr + 0x38),
                  (*(unsigned int *)(ptr + 0x2c) << 16) >> 13,
                  *(unsigned short *)(ptr + 0x30) << 3);
    *(unsigned short *)(ptr + 0x32) |= 1;
}
