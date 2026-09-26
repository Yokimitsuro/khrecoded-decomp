extern int func_02016a24(void *ptr, unsigned int value);
extern void *func_02016a6c(void *ptr, int value);

void func_02001a14(int *ptr, int *out, unsigned int value) {
    int *inner = (int *)ptr[0];
    int index = func_02016a24(inner, value);
    unsigned char *data;

    if (index == 0xffff) {
        index = *(unsigned short *)(inner[0] + 2);
    }

    out[0] = (int)func_02016a6c(inner, index);
    data = *(unsigned char **)(inner[0] + 8);
    out[1] = (int)(data + 8 + index * *(unsigned short *)(data + 2));
}
