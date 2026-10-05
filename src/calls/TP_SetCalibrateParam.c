#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/gx.h"

typedef int PXIFifoTag;
typedef u32 REGType32;
typedef u64 REGType64;
typedef int TPRequestCommand;
typedef int TPRequestResult;
enum { TP_RESULT_SUCCESS = 0, TP_RESULT_INVALID_PARAMETER, TP_RESULT_ILLEGAL_STATUS, TP_RESULT_EXCLUSIVE, TP_RESULT_PXI_BUSY };
enum { TP_STATE_READY = 0, TP_STATE_SAMPLING, TP_STATE_AUTO_SAMPLING, TP_STATE_AUTO_WAIT_END };
#define SPI_PXI_END_BIT                     0x01000000
#define SPI_PXI_DATA_MASK                   0x0000ffff
#define SPI_PXI_COMMAND_TP_SAMPLING         0x0000
#define SPI_PXI_COMMAND_TP_AUTO_ON          0x0001
#define SPI_PXI_COMMAND_TP_AUTO_OFF         0x0002
#define SPI_PXI_COMMAND_TP_AUTO_SAMPLING    0x0010
#define SPI_PXI_RESULT_SUCCESS              0x0000
#define SPI_PXI_RESULT_INVALID_COMMAND      0x0001
#define SPI_PXI_RESULT_INVALID_PARAMETER    0x0002
#define SPI_PXI_RESULT_ILLEGAL_STATUS       0x0003
#define SPI_PXI_RESULT_EXCLUSIVE            0x0004
#define TP_RAW_MAX  0x1000
#define TP_CALIBRATE_DOT_SCALE_SHIFT        8
#define TP_CALIBRATE_ORIGIN_SCALE_SHIFT     2
#define reg_CP_DIVCNT (*(REGType16v *)REG_DIVCNT_ADDR)

typedef struct {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TPData;

typedef struct NvTpData {
    s16 x0;
    s16 y0;
    s16 xDotSize;
    s16 yDotSize;
} TPCalibrateParam;

typedef void (*TPRecvCallback)(TPRequestCommand command, TPRequestResult result, u16 index);

typedef union SPITpData {
    struct {
        u32 x : 12;
        u32 y : 12;
        u32 touch : 1;
        u32 validity : 2;
        u32 dummy : 5;
    } e;
    u32 raw;
    u8 bytes[4];
    u16 halfs[2];
} SPITpData;

typedef struct {
    s32 x0;
    s32 xDotSize;
    s32 xDotSizeInv;
    s32 y0;
    s32 yDotSize;
    s32 yDotSizeInv;
} TPiCalibrateParam;

typedef struct {
    u16 raw_x1;
    u16 raw_y1;
    u8 dx1;
    u8 dy1;
    u16 raw_x2;
    u16 raw_y2;
    u8 dx2;
    u8 dy2;
} NVRAMConfigTp;
typedef struct {
    u8 head[0x58];
    NVRAMConfigTp tp;
} NVRAMConfigNcd;
typedef struct {
    NVRAMConfigNcd ncd;
} NVRAMConfig;

extern struct {
    u32 reserved0;
    TPRecvCallback callback;
    TPData buf;
    u16 index;
    u16 frequence;
    TPData *samplingBufs;
    u16 bufSize;
    u16 reserved1a;
    TPiCalibrateParam calibrate;
    u16 calibrate_flg;
    vu16 state;
    vu16 err_flg;
    vu16 command_flg;
} data_02059784;
#define tpState data_02059784

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_Terminate(void);
extern u32 TP_CalcCalibrateParam(TPCalibrateParam *calibrate, u16 raw_x1, u16 raw_y1, u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2, u16 dx2, u16 dy2);

static inline void CP_SetDivImm32_32_NS_(u32 numer, u32 denom)
{
    *(REGType32 *)REG_DIV_NUMER_ADDR = numer;
    *(REGType64 *)REG_DIV_DENOM_ADDR = denom;
}

static inline void CP_SetDiv32_32(u32 numer, u32 denom)
{
    reg_CP_DIVCNT = CP_DIV_32_32BIT_MODE;
    CP_SetDivImm32_32_NS_(numer, denom);
}

static inline u32 CP_IsDivBusy(void)
{
    return (reg_CP_DIVCNT & REG_CP_DIVCNT_BUSY_MASK);
}

static inline void CP_WaitDiv(void)
{
    while (CP_IsDivBusy()) {
    }
}

static inline s32 CP_GetDivResultImm32(void)
{
    return (s32)(*(REGType32 *)REG_DIV_RESULT_ADDR);
}

static inline s32 CP_GetDivResult32(void)
{
    CP_WaitDiv();
    return CP_GetDivResultImm32();
}

static inline void TPi_CopyTpFromSystemWork(TPData *result)
{
    SPITpData spi_tp;

    spi_tp.halfs[0] = *(u16 *)((u8 *)HW_TOUCHPANEL_BUF + 0);
    spi_tp.halfs[1] = *(u16 *)((u8 *)HW_TOUCHPANEL_BUF + 2);

    result->x = (u16)spi_tp.e.x;
    result->y = (u16)spi_tp.e.y;
    result->touch = (u8)spi_tp.e.touch;
    result->validity = (u8)spi_tp.e.validity;
}

static inline void TPi_ErrorAtPxi(TPRequestCommand command)
{
    tpState.err_flg |= (1 << command);

    if (tpState.callback) {
        (tpState.callback)(command, TP_RESULT_PXI_BUSY, 0);
    }
}

void TP_SetCalibrateParam (const TPCalibrateParam * param)
{
    OSIntrMode enabled;

    if (param == NULL) {
        tpState.calibrate_flg = FALSE;
        return;
    }

    enabled = OS_DisableInterrupts();

    if (param->xDotSize != 0) {
        CP_SetDiv32_32(0x10000000, (u32)param->xDotSize);

        tpState.calibrate.x0 = param->x0;
        tpState.calibrate.xDotSize = param->xDotSize;
        tpState.calibrate.xDotSizeInv = (s32)CP_GetDivResult32();
    } else {
        tpState.calibrate.x0 = 0;
        tpState.calibrate.xDotSize = 0;
        tpState.calibrate.xDotSizeInv = 0;
    }

    if (param->yDotSize != 0) {
        CP_SetDiv32_32(0x10000000, (u32)param->yDotSize);

        tpState.calibrate.y0 = param->y0;
        tpState.calibrate.yDotSize = param->yDotSize;
        tpState.calibrate.yDotSizeInv = (s32)CP_GetDivResult32();
    } else {
        tpState.calibrate.y0 = 0;
        tpState.calibrate.yDotSize = 0;
        tpState.calibrate.yDotSizeInv = 0;
    }

    (void)OS_RestoreInterrupts(enabled);

    tpState.calibrate_flg = TRUE;

}
