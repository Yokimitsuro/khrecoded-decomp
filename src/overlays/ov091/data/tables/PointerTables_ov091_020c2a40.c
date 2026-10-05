#include "nitro/types.h"

extern u8 sOv091_UiReportTopP2f_020c2a7c[];
extern u8 sOv091_UiReportLanguageTopP2f_020c2a90[];
extern u8 sOv091_UiReportLanguageTopObjP2f_020c2aa4[];
extern u8 sOv091_UiReportTextLanguageTopSZ_020c2abc[];

void *gReportTopResourcePaths[3] = {
    sOv091_UiReportTopP2f_020c2a7c,
    sOv091_UiReportLanguageTopP2f_020c2a90,
    sOv091_UiReportLanguageTopObjP2f_020c2aa4,
};

void *gReportTopTextPath[1] = {
    sOv091_UiReportTextLanguageTopSZ_020c2abc,
};
