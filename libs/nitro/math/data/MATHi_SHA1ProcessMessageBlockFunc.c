typedef void (*MATHSHA1ProcessBlockFunc)(void *context);

extern void MATHi_SHA1ProcessBlock(void *context);

MATHSHA1ProcessBlockFunc MATHi_SHA1ProcessMessageBlockFunc =
    MATHi_SHA1ProcessBlock;