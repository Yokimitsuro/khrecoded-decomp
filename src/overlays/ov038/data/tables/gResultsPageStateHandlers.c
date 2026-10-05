#include "nitro/types.h"

extern void func_ov038_020ba780(void);
extern void ShowOv038ResultsFadeIn(void); /* ShowOv038ResultsFadeIn */
extern void HandleOv038PageInput(void); /* HandleOv038PageInput */
extern void AdvanceOv038ExitTimer(void); /* AdvanceOv038ExitTimer */
extern void StopOv038SoundStream(void); /* StopOv038SoundStream */

void (*const gResultsPageStateHandlers[5])(void) = {
    func_ov038_020ba780,
    ShowOv038ResultsFadeIn, /* ShowOv038ResultsFadeIn */
    HandleOv038PageInput, /* HandleOv038PageInput */
    AdvanceOv038ExitTimer, /* AdvanceOv038ExitTimer */
    StopOv038SoundStream, /* StopOv038SoundStream */
};
