#pragma thumb on
extern void SoundMgr_Update(void);
extern int IsSceneState1(void);

enum { SCHED_BUSY = 0, SCHED_IDLE = 1 };

int Script_StepAndIsIdle(void)
{
    SoundMgr_Update();
    return IsSceneState1() != 0 ? SCHED_BUSY : SCHED_IDLE;
}
