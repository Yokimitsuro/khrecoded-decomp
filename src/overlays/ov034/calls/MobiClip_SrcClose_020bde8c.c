#include "nitro/types.h"

extern int data_ov034_020be940;
extern void *PXI_Init_0202a64c(int handle);

/* Releases the MobiClip source handle and invalidates it */
void MobiClip_SrcClose_020bde8c(void) {
    PXI_Init_0202a64c(data_ov034_020be940);
    data_ov034_020be940 = -1;
}
