extern void *func_02013620(void *p);
extern void MIi_CpuClear32(unsigned int data, void *dst, unsigned int size);

typedef struct {
    char _0[0x20];
    unsigned int flags;
    char _24[4];
    unsigned int size;
} X02010ce4;

void *func_02013638(X02010ce4 *p)
{
    void *out = func_02013620(&p->_24);

    if (out != 0) {
        unsigned char flags = p->flags;
        unsigned int size = p->size;

        if (flags & 1)
            MIi_CpuClear32(0, out, size);
    }

    return out;
}
