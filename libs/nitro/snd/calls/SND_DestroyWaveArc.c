/* Unlinks and clears the whole wave-archive chain under the sound mutex. */
extern void func_0200eddc(void);
extern void func_0200edf0(void);
extern void DC_StoreRange(void *p, unsigned int len);

void SND_DestroyWaveArc(int **owner) {
    int *node;
    int zero;
    int len;
    int *next;
    func_0200eddc();
    node = (int *)owner[6];
    if (node != 0) {
        zero = 0;
        len = 8;
        do {
            next = (int *)node[1];
            node[0] = zero;
            node[1] = zero;
            DC_StoreRange(node, len);
            node = next;
        } while (next != 0);
    }
    func_0200edf0();
}
