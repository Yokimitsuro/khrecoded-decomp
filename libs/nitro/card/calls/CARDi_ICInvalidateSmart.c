typedef unsigned long u32;

extern void IC_InvalidateAll(void);
extern void IC_InvalidateRange(void *buffer, u32 length);

void CARDi_ICInvalidateSmart(void *buffer, u32 length, u32 threshold)
{
    if (length >= threshold) {
        IC_InvalidateAll();
    } else {
        IC_InvalidateRange(buffer, length);
    }
}