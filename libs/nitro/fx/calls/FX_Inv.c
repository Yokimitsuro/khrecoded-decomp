extern void FX_InvAsync(int denominator);
extern int FX_GetDivResult(void);

int FX_Inv(int denominator)
{
    FX_InvAsync(denominator);
    return FX_GetDivResult();
}
