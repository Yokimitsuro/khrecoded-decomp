typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDDmaInterface {
    void (*receive)(u32 channel, const void *source, void *destination, u32 length);
    void (*stop)(u32 channel);
} CARDDmaInterface;

enum {
    MI_DMA_MAX_NUM = 3,
    MI_DMA_USING_NEW = 0x10
};

extern const CARDDmaInterface CARDiDmaUsingFormer;
extern void OS_Terminate(void);

const CARDDmaInterface *CARDi_GetDmaInterface(u32 channel)
{
    const CARDDmaInterface *result = 0;
    BOOL usesNewDma = (channel & MI_DMA_USING_NEW) != 0;

    channel &= ~MI_DMA_USING_NEW;
    if (channel <= MI_DMA_MAX_NUM) {
        if (!usesNewDma) {
            result = &CARDiDmaUsingFormer;
        } else {
            OS_Terminate();
        }
    }
    return result;
}