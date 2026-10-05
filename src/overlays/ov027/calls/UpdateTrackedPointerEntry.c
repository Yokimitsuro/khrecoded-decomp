typedef void (*fn0)(void);
typedef void (*fn1)(int);
struct key { unsigned short a, b, c, d; };
struct bit0 { unsigned int b : 1; };
extern int func_ov027_020b7a50(int obj, struct key *out);
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern int func_ov027_020b7880(unsigned int a, unsigned int b, int e);
extern void MI_CpuCopy8(void *dst, void *src, unsigned int n);
void UpdateTrackedPointerEntry(unsigned int *param_1, unsigned int param_2, unsigned int param_3,
                         unsigned int param_4) {
    struct key k;
    int e;
    int flag = 1;
    struct key *snap = (struct key *)((char *)param_1 + 0x1c);

    if (!func_ov027_020b7a50((int)param_1, &k)) goto done;
    if ((k.c ^ snap->c) == 0) goto done;
    if (k.c != 0) {
        if (k.d == 0) {
            for (e = (int)NNS_FndGetNextListObject(param_1, 0); e != 0;
                 e = (int)NNS_FndGetNextListObject(param_1, (void *)e)) {
                if (*(int *)(e + 0x24) != 0 && ((struct bit0 *)(e + 0x20))->b != 0 &&
                    func_ov027_020b7880(k.a, k.b, e)) {
                    MI_CpuCopy8(&k, snap, 8);
                    flag = 0;
                    (*(fn1) * (int *)(e + 0x24))(e);
                    param_1[6] = e;
                    if (*(int *)(e + 0x28) != 0) {
                        (*(fn1)param_1[0xf])(*(int *)(e + 0x28));
                    }
                    break;
                }
            }
        }
    } else {
        if (param_1[6] != 0 && *(int *)(param_1[6] + 0x28) != 0) {
            (*(fn1)param_1[0xf])(param_1[6]);
            param_1[6] = 0;
        }
    }
done:
    if (flag) {
        MI_CpuCopy8(&k, snap, 8);
    }
}
