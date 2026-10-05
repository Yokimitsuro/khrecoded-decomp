extern double func_02023650(int value);
extern double func_02022e34(double a, double b);

double ComputeSignedDifferenceAsDouble(int a, int b)
{
    if (a >= b) {
        return func_02023650(a - b);
    }
    return func_02022e34(0.0, func_02023650(b - a));
}
