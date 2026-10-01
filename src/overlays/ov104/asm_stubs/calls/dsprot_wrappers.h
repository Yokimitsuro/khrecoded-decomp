#ifndef DSPROT_WRAPPERS_H
#define DSPROT_WRAPPERS_H

typedef unsigned long u32;

extern unsigned char BSS;
extern const u32 Garbage[];
extern u32 Encryptor_DecryptionWrapperFragment(void);
extern void Encryptor_DecodeFunctionTable(void *functions);

#endif