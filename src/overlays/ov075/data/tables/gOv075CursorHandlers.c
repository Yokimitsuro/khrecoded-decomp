#include "nitro/types.h"

extern void func_ov075_020cc908(void); /* _fp_init */
extern void func_ov075_020cc934(void); /* _fp_init */
extern void StepScrollTowardTarget(void);
extern void MoveCursorToSelectedColumn(void); /* MoveCursorToSelectedColumn */
extern void func_ov075_020cc90c(void); /* _fp_init */

void (*const gOv075CursorHandlers[5])(void) = {
    func_ov075_020cc908, /* _fp_init */
    func_ov075_020cc934, /* _fp_init */
    StepScrollTowardTarget,
    MoveCursorToSelectedColumn, /* MoveCursorToSelectedColumn */
    func_ov075_020cc90c, /* _fp_init */
};
