#include "nitro/types.h"

typedef struct SceneSpawn {
    s16 roomId;
    s16 spawnX;
    u8 spawnY;
    u8 pad_05;
} SceneSpawn;

typedef struct SceneSpawnTable {
    SceneSpawn entries[8];
} SceneSpawnTable;

typedef struct SceneArgs {
    s16 unk_00;
    s16 unk_02;
    u8 kind;
    u8 spawnX;
    u8 spawnY;
} SceneArgs;

extern const SceneSpawnTable data_ov001_0209d8c8;
extern SceneArgs data_02060850;

extern void func_ov001_0206317c(int sceneId, int roomId, int mode, int param);

void EnterSceneSlotAtSpawn(int slot, BOOL alternate)
{
    int sceneId = (slot + 1) * 100;
    SceneSpawnTable table = data_ov001_0209d8c8;
    int roomId = table.entries[slot].roomId;
    int spawnX = table.entries[slot].spawnX;
    int spawnY = table.entries[slot].spawnY;

    if (slot == 6 && alternate) {
        roomId = 0x28;
        spawnX = 0xe;
        spawnY = 0x16;
    }
    func_ov001_0206317c(sceneId, roomId, 1, 3);
    data_02060850.spawnX = spawnX;
    data_02060850.spawnY = spawnY;
}
