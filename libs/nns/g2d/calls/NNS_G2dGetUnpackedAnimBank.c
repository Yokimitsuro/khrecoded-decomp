typedef int BOOL;

extern BOOL GetUnpackedAnimBankImpl_(void *, void **);

BOOL NNS_G2dGetUnpackedAnimBank(void *nanrFile, void **animBank)
{
    return GetUnpackedAnimBankImpl_(nanrFile, animBank);
}
