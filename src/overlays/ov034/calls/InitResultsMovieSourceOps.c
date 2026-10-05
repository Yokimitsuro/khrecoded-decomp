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
} MovieSourceOps;

extern void func_ov034_020bde10(void);
extern void IsResultsInputEnabled(void);
extern void ClearResultsFlagTwo(void);
extern void MarkResultsComplete(void);
extern void MobiClip_SrcIsOpen_020bde70(void);
extern void MobiClip_SrcClose_020bde8c(void);
extern void func_ov034_020bdea4(void);

void InitResultsMovieSourceOps(MovieSourceOps *ops)
{
    ops->open = func_ov034_020bde10;
    ops->op1 = IsResultsInputEnabled;
    ops->op2 = ClearResultsFlagTwo;
    ops->op3 = MarkResultsComplete;
    ops->isOpen = MobiClip_SrcIsOpen_020bde70;
    ops->close = MobiClip_SrcClose_020bde8c;
    ops->op6 = NULL;
    ops->op7 = func_ov034_020bdea4;
    ops->op8 = NULL;
}
