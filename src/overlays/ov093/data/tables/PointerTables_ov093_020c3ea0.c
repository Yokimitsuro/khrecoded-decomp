#include "nitro/types.h"

extern u8 sOv093_UiReportTextLanguageTrophySZ_020c3f08[];
extern u8 sOv093_UiReportTextLanguageTrophyNameSZ_020c3f24[];
extern u8 sOv093_UiReportTextLanguageTrophyDetailSZ_020c3f48[];
extern u8 sOv093_UiReportTextLanguageTrophyAchievementSZ_020c3f6c[];
extern u8 sOv093_UiReportTrophyP2f_020c3ebc[];
extern u8 sOv093_UiReportLanguageTrophyP2f_020c3ed4[];
extern u8 sOv093_UiReportLanguageTrophyObjP2f_020c3eec[];

void *gTrophyReportTextPaths[4] = {
    sOv093_UiReportTextLanguageTrophySZ_020c3f08,
    sOv093_UiReportTextLanguageTrophyNameSZ_020c3f24,
    sOv093_UiReportTextLanguageTrophyDetailSZ_020c3f48,
    sOv093_UiReportTextLanguageTrophyAchievementSZ_020c3f6c,
};

void *gTrophyReportResourcePaths[3] = {
    sOv093_UiReportTrophyP2f_020c3ebc,
    sOv093_UiReportLanguageTrophyP2f_020c3ed4,
    sOv093_UiReportLanguageTrophyObjP2f_020c3eec,
};
