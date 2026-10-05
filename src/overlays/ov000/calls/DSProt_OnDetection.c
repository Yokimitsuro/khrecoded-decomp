extern void InitDifficultyConfigBlock(int enabled);
extern void SetPendingScene(int mode, int value);

void DSProt_OnDetection(void) {
    InitDifficultyConfigBlock(1);
    SetPendingScene(2, 0);
}
