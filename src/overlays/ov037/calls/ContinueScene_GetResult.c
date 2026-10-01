typedef struct ContinueSceneState {
    unsigned char reserved[0x1c];
    int result;
} ContinueSceneState;

extern ContinueSceneState *gContinueSceneState;

int ContinueScene_GetResult(void)
{
    return gContinueSceneState->result;
}
