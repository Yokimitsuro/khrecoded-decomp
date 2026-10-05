#include "nitro/types.h"

extern u8 sOv095_UiReportItemP2f_020c17f0[];
extern u8 sOv095_UiReportLanguageItemP2f_020c1804[];
extern u8 sOv095_UiReportLanguageItemImdP2f_020c181c[];
extern u8 sOv095_UiReportTextLanguageItemSZ_020c1854[];
extern u8 sOv095_UiMenuStrLanguageMatrixSZ_020c1838[];

void *gItemReportResourcePaths[3] = {
    sOv095_UiReportItemP2f_020c17f0,
    sOv095_UiReportLanguageItemP2f_020c1804,
    sOv095_UiReportLanguageItemImdP2f_020c181c,
};

void *gItemReportTextPaths[2] = {
    sOv095_UiReportTextLanguageItemSZ_020c1854,
    sOv095_UiMenuStrLanguageMatrixSZ_020c1838,
};
