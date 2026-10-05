#include "nitro/types.h"

extern void GX_LoadBG0Char(void); /* GX_LoadBG0Char */
extern void GX_LoadBGPltt(void); /* func */
extern void SetMainBg1Control(void); /* func_0202adb0 */
extern void G2_GetBG1ScrPtr(void); /* G2_GetBG1ScrPtr */
extern void GX_LoadBG1Scr(void); /* GX_LoadBG1Scr */
extern void GX_LoadBG1Char(void); /* GX_LoadBG1Char */
extern void SetMainBg2Control(void); /* func_0202ad84 */
extern void G2_GetBG2ScrPtr(void); /* G2_GetBG2ScrPtr */
extern void GX_LoadBG2Scr(void); /* GX_LoadBG2Scr */
extern void GX_LoadBG2Char(void); /* GX_LoadBG2Char */
extern void SetMainBg3Control(void); /* func_0202ad58 */
extern void G2_GetBG3ScrPtr(void); /* G2_GetBG3ScrPtr */
extern void GX_LoadBG3Scr(void); /* GX_LoadBG3Scr */
extern void GX_LoadBG3Char(void); /* GX_LoadBG3Char */
extern void SetSubBg0Control(void); /* func_0202ad24 */
extern void G2S_GetBG0ScrPtr(void); /* G2S_GetBG0ScrPtr */
extern void GXS_LoadBG0Scr(void); /* GXS_LoadBG0Scr */
extern void GXS_LoadBG0Char(void); /* GXS_LoadBG0Char */
extern void GXS_LoadBGPltt(void); /* GXS_LoadBGPltt */
extern void SetSubBg1Control(void); /* func_0202acf0 */
extern void G2S_GetBG1ScrPtr(void); /* G2S_GetBG1ScrPtr */
extern void GXS_LoadBG1Scr(void); /* GXS_LoadBG1Scr */
extern void GXS_LoadBG1Char(void); /* GXS_LoadBG1Char */
extern void SetEngineBBG2Control(void); /* SetEngineBBG2Control */
extern void G2S_GetBG2ScrPtr(void); /* G2S_GetBG2ScrPtr */
extern void GXS_LoadBG2Scr(void); /* GXS_LoadBG2Scr */
extern void GXS_LoadBG2Char(void); /* GXS_LoadBG2Char */
extern void SetEngineBBG3Control(void); /* SetEngineBBG3Control */
extern void G2S_GetBG3ScrPtr(void); /* G2S_GetBG3ScrPtr */
extern void GXS_LoadBG3Scr(void); /* GXS_LoadBG3Scr */
extern void GXS_LoadBG3Char(void); /* GXS_LoadBG3Char */
extern void G2_GetBG0ScrPtr(void); /* G2_GetBG0ScrPtr */
extern void GX_LoadBG0Scr(void); /* GX_LoadBG0Scr */

void (*const gBgLayerTransferDispatch[44])(void) = {
    GX_LoadBG0Char, /* GX_LoadBG0Char */
    GX_LoadBGPltt, /* func */
    SetMainBg1Control, /* func_0202adb0 */
    NULL,
    G2_GetBG1ScrPtr, /* G2_GetBG1ScrPtr */
    GX_LoadBG1Scr, /* GX_LoadBG1Scr */
    GX_LoadBG1Char, /* GX_LoadBG1Char */
    GX_LoadBGPltt, /* func */
    NULL,
    SetMainBg2Control, /* func_0202ad84 */
    G2_GetBG2ScrPtr, /* G2_GetBG2ScrPtr */
    GX_LoadBG2Scr, /* GX_LoadBG2Scr */
    GX_LoadBG2Char, /* GX_LoadBG2Char */
    GX_LoadBGPltt, /* func */
    NULL,
    SetMainBg3Control, /* func_0202ad58 */
    G2_GetBG3ScrPtr, /* G2_GetBG3ScrPtr */
    GX_LoadBG3Scr, /* GX_LoadBG3Scr */
    GX_LoadBG3Char, /* GX_LoadBG3Char */
    GX_LoadBGPltt, /* func */
    SetSubBg0Control, /* func_0202ad24 */
    NULL,
    G2S_GetBG0ScrPtr, /* G2S_GetBG0ScrPtr */
    GXS_LoadBG0Scr, /* GXS_LoadBG0Scr */
    GXS_LoadBG0Char, /* GXS_LoadBG0Char */
    GXS_LoadBGPltt, /* GXS_LoadBGPltt */
    SetSubBg1Control, /* func_0202acf0 */
    NULL,
    G2S_GetBG1ScrPtr, /* G2S_GetBG1ScrPtr */
    GXS_LoadBG1Scr, /* GXS_LoadBG1Scr */
    GXS_LoadBG1Char, /* GXS_LoadBG1Char */
    GXS_LoadBGPltt, /* GXS_LoadBGPltt */
    NULL,
    SetEngineBBG2Control, /* SetEngineBBG2Control */
    G2S_GetBG2ScrPtr, /* G2S_GetBG2ScrPtr */
    GXS_LoadBG2Scr, /* GXS_LoadBG2Scr */
    GXS_LoadBG2Char, /* GXS_LoadBG2Char */
    GXS_LoadBGPltt, /* GXS_LoadBGPltt */
    NULL,
    SetEngineBBG3Control, /* SetEngineBBG3Control */
    G2S_GetBG3ScrPtr, /* G2S_GetBG3ScrPtr */
    GXS_LoadBG3Scr, /* GXS_LoadBG3Scr */
    GXS_LoadBG3Char, /* GXS_LoadBG3Char */
    GXS_LoadBGPltt, /* GXS_LoadBGPltt */
};

void (*const gBg0TransferDispatch[2])(void) = {
    G2_GetBG0ScrPtr, /* G2_GetBG0ScrPtr */
    GX_LoadBG0Scr, /* GX_LoadBG0Scr */
};
