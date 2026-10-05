extern int IsSceneState1();
extern void func_0202c44c();

void SoundMgr_WaitLoaderIfState1(void)
{
    if (IsSceneState1()) func_0202c44c();
}
