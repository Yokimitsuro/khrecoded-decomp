#include "nitro/types.h"

extern void OS_SetProtectionRegion0(void); /* func */
extern void OS_SetProtectionRegion1(void); /* func */
extern void OS_SetProtectionRegion2(void); /* func */
extern void OS_SetProtectionRegion3(void); /* func */
extern void OS_SetProtectionRegion4(void); /* func */
extern void OS_SetProtectionRegion5(void); /* func */
extern void OS_SetProtectionRegion6(void); /* func */
extern void OS_SetProtectionRegion7(void); /* func */
extern void OS_GetProtectionRegion0(void); /* func */
extern void OS_GetProtectionRegion1(void); /* func */
extern void OS_GetProtectionRegion2(void); /* func */
extern void OS_GetProtectionRegion3(void); /* func */
extern void OS_GetProtectionRegion4(void); /* func */
extern void OS_GetProtectionRegion5(void); /* func */
extern void OS_GetProtectionRegion6(void); /* func */
extern void OS_GetProtectionRegion7(void); /* func */

void (*OSi_ProtectionRegionSetters[16])(void) = {
    OS_SetProtectionRegion0, /* func */
    OS_SetProtectionRegion1, /* func */
    OS_SetProtectionRegion2, /* func */
    OS_SetProtectionRegion3, /* func */
    OS_SetProtectionRegion4, /* func */
    OS_SetProtectionRegion5, /* func */
    OS_SetProtectionRegion6, /* func */
    OS_SetProtectionRegion7, /* func */
    OS_GetProtectionRegion0, /* func */
    OS_GetProtectionRegion1, /* func */
    OS_GetProtectionRegion2, /* func */
    OS_GetProtectionRegion3, /* func */
    OS_GetProtectionRegion4, /* func */
    OS_GetProtectionRegion5, /* func */
    OS_GetProtectionRegion6, /* func */
    OS_GetProtectionRegion7, /* func */
};
