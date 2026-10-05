#include "nitro/types.h"

extern void func_ov036_020bf6dc(void);
extern void func_ov036_020bf6e0(void);
extern void func_ov036_020bfb2c(void); /* LoadTextWindowFrame */
extern void func_ov036_020bfe38(void);
extern void func_ov036_020c0348(void);
extern void func_ov036_020c0400(void);
extern void func_ov036_020c0d54(void); /* UpdateTextWindowTyping */
extern void func_ov036_020c0e30(void);
extern void func_ov036_020c0e34(void); /* AdvanceTextWindowPage */
extern void func_ov036_020c1188(void);
extern void func_ov036_020c1254(void); /* CloseTextWindowEntry */
extern void func_ov036_020c1308(void);
extern void func_ov036_020c182c(void);
extern void func_ov036_020c1d48(void);

void (*const gTextWindowStateHandlers[14])(void) = {
    func_ov036_020bf6dc,
    func_ov036_020bf6e0,
    func_ov036_020bfb2c, /* LoadTextWindowFrame */
    func_ov036_020bfe38,
    func_ov036_020c0348,
    func_ov036_020c0400,
    func_ov036_020c0d54, /* UpdateTextWindowTyping */
    func_ov036_020c0e30,
    func_ov036_020c0e34, /* AdvanceTextWindowPage */
    func_ov036_020c1188,
    func_ov036_020c1254, /* CloseTextWindowEntry */
    func_ov036_020c1308,
    func_ov036_020c182c,
    func_ov036_020c1d48,
};
