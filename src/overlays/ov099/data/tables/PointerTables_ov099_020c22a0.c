#include "nitro/types.h"

extern u8 sOv099_UiReportEnemyP2f_020c22e0[];
extern u8 sOv099_UiReportLanguageEnemyP2f_020c22f4[];
extern u8 sOv099_UiReportLanguageEnemyObjP2f_020c230c[];
extern u8 sOv099_UiReportTextLanguageEnemySZ_020c2328[];
extern u8 data_ov099_020c2344[];

void *gEnemyReportResourcePaths[3] = {
    sOv099_UiReportEnemyP2f_020c22e0,
    sOv099_UiReportLanguageEnemyP2f_020c22f4,
    sOv099_UiReportLanguageEnemyObjP2f_020c230c,
};

void *gEnemyReportTextPaths[2] = {
    sOv099_UiReportTextLanguageEnemySZ_020c2328,
    data_ov099_020c2344,
};
