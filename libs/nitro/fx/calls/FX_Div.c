extern void FX_DivAsync(int numerator, int denominator);
extern int FX_GetDivResult(void);

int FX_Div(int numerator, int denominator)
{
    FX_DivAsync(numerator, denominator);
    return FX_GetDivResult();
}
