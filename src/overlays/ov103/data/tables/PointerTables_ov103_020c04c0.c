#include "nitro/types.h"

extern u8 data_ov103_020c055c[];
extern u8 sOv103_UiReportTextLanguageTheaterMovieSZ_020c05a0[];
extern u8 sOv103_UiReportTextLanguageTheaterTimeSZ_020c057c[];
extern u8 sOv103_UiReportTheaterP2f_020c052c[];
extern u8 sOv103_UiReportLanguageTheaterP2f_020c0544[];

void *gTheaterReportTextPaths[3] = {
    data_ov103_020c055c,
    sOv103_UiReportTextLanguageTheaterMovieSZ_020c05a0,
    sOv103_UiReportTextLanguageTheaterTimeSZ_020c057c,
};

void *gTheaterReportResourcePaths[2] = {
    sOv103_UiReportTheaterP2f_020c052c,
    sOv103_UiReportLanguageTheaterP2f_020c0544,
};
