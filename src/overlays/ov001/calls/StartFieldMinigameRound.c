#include "nitro/types.h"

typedef struct LevelTable {
    int values[4];
} LevelTable;

typedef struct FieldMinigame {
    int mode;
    u8 pad_04[0x1c];
    int active;
    u8 pad_24[0xac - 0x24];
    int score;
    int level;
} FieldMinigame;

extern FieldMinigame *data_ov001_020a04f4;
extern LevelTable data_ov001_0209e088;
extern LevelTable data_ov001_0209e098;
extern void *GetSceneTagTracker(void);
extern int func_ov001_0207123c(void);
extern s32 GetClampedPaletteSlot(void);
extern void func_ov001_0207df6c(u32 param, int level);
extern void InitFieldSpriteSlots(FieldMinigame *game, BOOL useBlocks);
extern void func_ov001_0207e26c(FieldMinigame *game, s32 flag);
extern void RandomizeFacing(FieldMinigame *game, BOOL apply);
extern void func_ov027_020b9d74(int widgets, int layer, int x, int y, int width, int height);

void StartFieldMinigameRound(void)
{
    FieldMinigame *game = data_ov001_020a04f4;
    int widgets;
    LevelTable levels;
    LevelTable times;
    int scale;

    GetSceneTagTracker();
    widgets = func_ov001_0207123c();
    levels = data_ov001_0209e088;
    times = data_ov001_0209e098;
    game->active = 1;
    scale = 20;
    game->score = 0;
    game->level = (levels.values[GetClampedPaletteSlot()] * 10 + 9) / 10;
    switch (game->mode) {
    case 1:
        InitFieldSpriteSlots(game, FALSE);
        scale = 15;
        break;
    case 2:
        func_ov001_0207e26c(game, 0);
        break;
    case 3:
        RandomizeFacing(game, FALSE);
        break;
    }
    func_ov027_020b9d74(widgets, 11, 0, 8, 11, 16);
    func_ov001_0207df6c(((scale * times.values[GetClampedPaletteSlot()] + 9) / 10) * 1000, game->level);
}
