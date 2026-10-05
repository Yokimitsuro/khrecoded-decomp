#include "nitro/types.h"

extern void func_ov032_020ba8c0(void); /* SetSlotDisplayStyle */
extern void func_ov032_020ba92c(void); /* LoadShadowAndFlagScene */
extern void func_ov032_020ba960(void); /* AcknowledgeGroupTransition */
extern void func_ov032_020ba98c(void);
extern void func_ov032_020ba9a4(void); /* FinishMovieMenuLoad */
extern void func_ov032_020baa28(void); /* ResumeSceneAndAdvance */
extern void func_ov032_020baaf0(void); /* CompleteGroupTransition */
extern void func_ov032_020bab24(void);
extern void func_ov032_020bb034(void); /* AdvanceToRoutedSlot */
extern void func_ov032_020bb14c(void); /* InitializeGroupAction */
extern void func_ov032_020bb170(void); /* FinishGroupTransition */
extern void func_ov032_020bb1cc(void); /* EnterState12WithHalfRate */
extern void func_ov032_020bb1e8(void); /* CommitGroupActionState */
extern void func_ov032_020bb218(void); /* EnterGroupActionState */
extern void func_ov032_020bb240(void); /* TryOpenGroupAction */
extern void func_ov032_020bb27c(void); /* FinishGroupActionState */
extern void func_ov032_020bb2a4(void);
extern void func_ov032_020bb350(void); /* ClearGroupTransitionFlags */

void (*gGroupActionStateHandlers[18])(void) = {
    func_ov032_020ba8c0, /* SetSlotDisplayStyle */
    func_ov032_020ba92c, /* LoadShadowAndFlagScene */
    func_ov032_020ba960, /* AcknowledgeGroupTransition */
    func_ov032_020ba98c,
    func_ov032_020ba9a4, /* FinishMovieMenuLoad */
    func_ov032_020baa28, /* ResumeSceneAndAdvance */
    func_ov032_020baaf0, /* CompleteGroupTransition */
    func_ov032_020bab24,
    func_ov032_020bb034, /* AdvanceToRoutedSlot */
    func_ov032_020bb14c, /* InitializeGroupAction */
    func_ov032_020bb170, /* FinishGroupTransition */
    func_ov032_020bb1cc, /* EnterState12WithHalfRate */
    func_ov032_020bb1e8, /* CommitGroupActionState */
    func_ov032_020bb218, /* EnterGroupActionState */
    func_ov032_020bb240, /* TryOpenGroupAction */
    func_ov032_020bb27c, /* FinishGroupActionState */
    func_ov032_020bb2a4,
    func_ov032_020bb350, /* ClearGroupTransitionFlags */
};
