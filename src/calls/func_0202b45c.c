extern int GFXi_EnqueueCommand(void *a, int b, int c, int d);
extern void *data_02055738[];

int func_0202b45c(int idx, void *p, int arg2, int arg3) {
    return GFXi_EnqueueCommand(data_02055738[idx], arg2, *(int *)((char *)p + 0x14), arg3);
}
