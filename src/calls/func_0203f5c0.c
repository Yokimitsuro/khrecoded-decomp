typedef struct { int a, b, c; } T3_020ad44c;
extern void GetSegmentPointAtHitTime(T3_020ad44c *out, int arg1, int arg2, int arg3);
void func_0203f5c0(int *arg0, int arg1, int arg2, int arg3) {
    T3_020ad44c tmp;
    GetSegmentPointAtHitTime(&tmp, arg1, arg2, arg3);
    *(T3_020ad44c *)arg0 = tmp;
}
