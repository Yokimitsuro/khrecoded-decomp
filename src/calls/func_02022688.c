extern void FloorDiv(int *out, int a, int b);
extern int TryAddInt32A(int *ptr, int addend);

int func_02022688(int *numerator, int denominator, int *accumulator, int unused)
{
    int out[2];
    FloorDiv(out, *numerator, denominator);
    *numerator = out[1];
    return TryAddInt32A(accumulator, out[0]);
}
