extern void *ResCache_FindSlot(int a, int b);
extern int func_0202c378(int a, int b);
extern void strcpy(void *dst, int src);
extern int Heap_GetCurrent(void);

extern int gFileLoader[];

typedef struct {
    unsigned short s0;
    unsigned short s2;
    unsigned short s4;
    unsigned short s6;
    int w8;
    int wc;
    int reserved10;
    int payload14;
} Slot_0201f468;

int AcquireSharedRecord(int a, Slot_0201f468 **out, int c) {
    Slot_0201f468 *p = (Slot_0201f468 *)ResCache_FindSlot(a, (int)out);
    int v;

    if (p->s0 != 0) {
        p->s0++;
        *out = p;
        gFileLoader[0x14 / 4] = 0;
        return 1;
    }

    v = gFileLoader[0x14 / 4];
    if (v == 0) {
        v = Heap_GetCurrent();
    }
    p->w8 = v;
    p->wc = func_0202c378(a, c);
    if (a & 0x80000000) {
        p->payload14 = a;
    } else {
        strcpy(&p->payload14, a);
    }
    p->s0 = 1;
    p->s2 = 0;
    p->s4 = 0;
    p->s6 = (unsigned short)c;
    *out = p;
    return 0;
}
