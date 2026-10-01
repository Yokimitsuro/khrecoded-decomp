typedef unsigned long u32;

typedef struct CARDBackupSpec {
    u32 totalSize;
    u32 sectorSize;
} CARDBackupSpec;

typedef struct CARDiCommandArg {
    u32 result;
    u32 type;
    u32 cardId;
    u32 source;
    u32 destination;
    u32 length;
    CARDBackupSpec backup;
} CARDiCommandArg;

typedef struct CARDiCommon {
    CARDiCommandArg *command;
} CARDiCommon;

extern CARDiCommon cardi_common;

u32 CARD_GetBackupSectorSize(void)
{
    return cardi_common.command->backup.sectorSize;
}
