typedef unsigned long u32;

enum {
    HW_CACHE_LINE_SIZE = 32
};

extern void DC_FlushAll(void);
extern void DC_StoreRange(void *buffer, u32 length);
extern void DC_InvalidateRange(void *buffer, u32 length);
extern void DC_WaitWriteBufferEmpty(void);

void CARDi_DCInvalidateSmart(void *buffer, u32 length, u32 threshold)
{
    if (length >= threshold) {
        DC_FlushAll();
    } else {
        u32 position = (u32)buffer;
        u32 misalignment = position & (HW_CACHE_LINE_SIZE - 1);

        if (misalignment) {
            position -= misalignment;
            DC_StoreRange((void *)position, HW_CACHE_LINE_SIZE);
            DC_StoreRange((void *)(position + length), HW_CACHE_LINE_SIZE);
            length += HW_CACHE_LINE_SIZE;
        }

        DC_InvalidateRange((void *)position, length);
        DC_WaitWriteBufferEmpty();
    }
}