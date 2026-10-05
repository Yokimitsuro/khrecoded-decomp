#include "nitro/types.h"

extern void func_ov001_0208f6e0(void); /* _fp_init */
extern void func_ov001_0208f6e4(void); /* SyncNearestEntryPosition */
extern void func_ov001_0208f708(void); /* _fp_init */
extern void func_ov001_0208f70c(void); /* _fp_init */

void (*gNearestEntrySyncHandlers[13])(void) = {
    NULL,
    NULL,
    NULL,
    NULL,
    func_ov001_0208f6e0, /* _fp_init */
    func_ov001_0208f6e4, /* SyncNearestEntryPosition */
    func_ov001_0208f708, /* _fp_init */
    func_ov001_0208f70c, /* _fp_init */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
