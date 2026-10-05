extern int AdvancePendingScene(void);

int UpdateSceneCallback(void)
{
    AdvancePendingScene();
    return 0;
}
