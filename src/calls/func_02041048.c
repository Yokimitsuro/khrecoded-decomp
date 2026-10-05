typedef struct { int a, b, c; } T3_020ad44c;
extern void SetVec3(T3_020ad44c *out, int arg1, int arg2, int arg3);
void func_02041048(int *arg0, int arg1, int arg2, int arg3) {
    T3_020ad44c tmp;
    SetVec3(&tmp, arg1, arg2, arg3);
    *(T3_020ad44c *)arg0 = tmp;
}
