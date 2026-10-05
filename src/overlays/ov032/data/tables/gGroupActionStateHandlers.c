#include "nitro/types.h"

extern void func_ov032_020ba8c0(void); /* SetSlotDisplayStyle */
extern void func_ov032_020ba92c(void); /* LoadShadowAndFlagScene */
extern void AcknowledgeGroupTransition(void); /* AcknowledgeGroupTransition */
extern void func_ov032_020ba98c(void);
extern void func_ov032_020ba9a4(void); /* FinishMovieMenuLoad */
extern void func_ov032_020baa28(void); /* ResumeSceneAndAdvance */
extern void CompleteGroupTransition(void); /* CompleteGroupTransition */
extern void func_ov032_020bab24(void);
extern void func_ov032_020bb034(void); /* AdvanceToRoutedSlot */
extern void InitializeGroupAction(void); /* InitializeGroupAction */
extern void FinishGroupTransition(void); /* FinishGroupTransition */
extern void EnterState12WithHalfRate_020bb1cc(void); /* EnterState12WithHalfRate */
extern void CommitGroupActionState(void); /* CommitGroupActionState */
extern void EnterGroupActionState(void); /* EnterGroupActionState */
extern void TryOpenGroupAction(void); /* TryOpenGroupAction */
extern void FinishGroupActionState(void); /* FinishGroupActionState */
extern void func_ov032_020bb2a4(void);
extern void ClearGroupTransitionFlags(void); /* ClearGroupTransitionFlags */

void (*gGroupActionStateHandlers[18])(void) = {
    func_ov032_020ba8c0, /* SetSlotDisplayStyle */
    func_ov032_020ba92c, /* LoadShadowAndFlagScene */
    AcknowledgeGroupTransition, /* AcknowledgeGroupTransition */
    func_ov032_020ba98c,
    func_ov032_020ba9a4, /* FinishMovieMenuLoad */
    func_ov032_020baa28, /* ResumeSceneAndAdvance */
    CompleteGroupTransition, /* CompleteGroupTransition */
    func_ov032_020bab24,
    func_ov032_020bb034, /* AdvanceToRoutedSlot */
    InitializeGroupAction, /* InitializeGroupAction */
    FinishGroupTransition, /* FinishGroupTransition */
    EnterState12WithHalfRate_020bb1cc, /* EnterState12WithHalfRate */
    CommitGroupActionState, /* CommitGroupActionState */
    EnterGroupActionState, /* EnterGroupActionState */
    TryOpenGroupAction, /* TryOpenGroupAction */
    FinishGroupActionState, /* FinishGroupActionState */
    func_ov032_020bb2a4,
    ClearGroupTransitionFlags, /* ClearGroupTransitionFlags */
};
