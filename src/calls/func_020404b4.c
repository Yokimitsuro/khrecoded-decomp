typedef struct { int a, b, c; } T3_020ad44c;
extern void GetUnitCrossReportDegenerate(T3_020ad44c *out, int arg1, int arg2, int arg3);
void func_020404b4(int *arg0, int arg1, int arg2, int arg3) {
    T3_020ad44c tmp;
    GetUnitCrossReportDegenerate(&tmp, arg1, arg2, arg3);
    *(T3_020ad44c *)arg0 = tmp;
}
