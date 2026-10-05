#include "nitro/types.h"

extern void func_ov022_020aa2fc(void);
extern void func_ov022_020a9294(void);
extern void func_ov022_020aa188(void); /* SeekBitstreamCursor */
extern void func_ov022_020aa1d4(void); /* readStreamBytesSynchronously */
extern void func_ov022_020aa244(void); /* beginAlignedFileReadAhead */
extern void func_ov022_020aa2c0(void);
extern void func_ov022_020aa2e8(void); /* CallVirt14 */

void (*gStreamIoCallbacks[7])(void) = {
    func_ov022_020aa2fc,
    func_ov022_020a9294,
    func_ov022_020aa188, /* SeekBitstreamCursor */
    func_ov022_020aa1d4, /* readStreamBytesSynchronously */
    func_ov022_020aa244, /* beginAlignedFileReadAhead */
    func_ov022_020aa2c0,
    func_ov022_020aa2e8, /* CallVirt14 */
};
