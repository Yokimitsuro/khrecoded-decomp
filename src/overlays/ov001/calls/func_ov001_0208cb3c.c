typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct Ov023Operand {
    s16  nType;
    u8   pad_02[6];
} Ov023Operand;

typedef struct Ov023RampCmd {
    Ov023Operand aOperand[4];
    int  nField20;
    int  nRemaining;
} Ov023RampCmd;

extern int   ScriptVm_ReadOperandInt(void *pCtx, Ov023Operand *pOperand);
extern int   ScriptVm_ReadOperandFx32(void *pCtx, Ov023Operand *pOperand);
extern void *func_02036254(u16 nEntity);
extern void  SetWorldObjectProbeSphere(u16 nEntity, int bEnable, int nDuration);
extern int   EvaluateInterpolationCurve(int nMode, int nTotal, int nRemaining);
extern int   ScaleAroundPivot(int nFactor, int nFrom, int nTo);
extern void  ScriptCmd_SetElemField(void *pCtx, void *pCmd);

int func_ov001_0208cb3c(void *pCtx, Ov023RampCmd *pCmd)
{
    int nActor;
    int nFrames;
    int nFrom;
    int nTo;

    nActor = ScriptVm_ReadOperandInt(pCtx, &pCmd->aOperand[0]);
    nFrames = ScriptVm_ReadOperandInt(pCtx, &pCmd->aOperand[3]);
    nFrom = ScriptVm_ReadOperandFx32(pCtx, &pCmd->aOperand[1]);
    nTo = ScriptVm_ReadOperandFx32(pCtx, &pCmd->aOperand[2]);
    func_02036254((u16)nActor);
    pCmd->nRemaining--;
    if (pCmd->nRemaining == 0) {
        SetWorldObjectProbeSphere((u16)nActor, 1, nTo);
        return 1;
    }
    SetWorldObjectProbeSphere((u16)nActor, 1, ScaleAroundPivot(EvaluateInterpolationCurve(2, nFrames, pCmd->nRemaining), nTo, nFrom));
    ScriptCmd_SetElemField(pCtx, pCmd);
    return 0;
}
