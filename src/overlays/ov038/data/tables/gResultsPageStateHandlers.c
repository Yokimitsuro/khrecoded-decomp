#include "nitro/types.h"

extern void func_ov038_020ba780(void);
extern void func_ov038_020ba788(void); /* ShowOv038ResultsFadeIn */
extern void func_ov038_020baab8(void); /* HandleOv038PageInput */
extern void func_ov038_020babd4(void); /* AdvanceOv038ExitTimer */
extern void StopOv038SoundStream(void); /* StopOv038SoundStream */

void (*const gResultsPageStateHandlers[5])(void) = {
    func_ov038_020ba780,
    func_ov038_020ba788, /* ShowOv038ResultsFadeIn */
    func_ov038_020baab8, /* HandleOv038PageInput */
    func_ov038_020babd4, /* AdvanceOv038ExitTimer */
    StopOv038SoundStream, /* StopOv038SoundStream */
};
