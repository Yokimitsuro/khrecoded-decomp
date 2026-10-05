#include "nitro/types.h"

extern void SetSlotDisplayStyle(void); /* SetSlotDisplayStyle */
extern void LoadShadowAndFlagScene(void); /* LoadShadowAndFlagScene */
extern void AcknowledgeGroupTransition(void); /* AcknowledgeGroupTransition */
extern void func_ov032_020ba98c(void);
extern void FinishMovieMenuLoad(void); /* FinishMovieMenuLoad */
extern void ResumeSceneAndAdvance(void); /* ResumeSceneAndAdvance */
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
    SetSlotDisplayStyle, /* SetSlotDisplayStyle */
    LoadShadowAndFlagScene, /* LoadShadowAndFlagScene */
    AcknowledgeGroupTransition, /* AcknowledgeGroupTransition */
    func_ov032_020ba98c,
    FinishMovieMenuLoad, /* FinishMovieMenuLoad */
    ResumeSceneAndAdvance, /* ResumeSceneAndAdvance */
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
