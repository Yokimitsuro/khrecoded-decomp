#include "nitro/types.h"

typedef struct MovieSourceOps {
    void *open;
    void *op1;
    void *op2;
    void *op3;
    void *isOpen;
    void *close;
    void *op6;
    void *op7;
    void *op8;
    void *unused9;
    void *op10;
} MovieSourceOps;

extern void func_ov035_020ba960(void);
extern void func_ov035_020ba978(void);
extern void func_ov035_020ba994(void);
extern void func_ov035_020ba9ac(void);
extern void MobiClip_SrcIsOpen_020ba9c4(void);
extern void MobiClip_SrcClose_020ba9e0(void);
extern void BeginMovieCaption(void);
extern void IsMovieWaitingForInput(void);
extern void func_ov035_020ba7fc(void);
extern void func_ov035_020baa38(void);
extern void ApplyAreaMusicEntry(int mode);

void InitMovieSourceOps(MovieSourceOps *ops) {
    ops->open = func_ov035_020ba960;
    ops->op1 = func_ov035_020ba978;
    ops->op2 = func_ov035_020ba994;
    ops->op3 = func_ov035_020ba9ac;
    ops->isOpen = MobiClip_SrcIsOpen_020ba9c4;
    ops->close = MobiClip_SrcClose_020ba9e0;
    ops->op6 = BeginMovieCaption;
    ops->op7 = IsMovieWaitingForInput;
    ops->op8 = func_ov035_020ba7fc;
    ops->op10 = func_ov035_020baa38;
    ApplyAreaMusicEntry(3);
}
