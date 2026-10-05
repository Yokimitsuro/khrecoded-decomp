typedef unsigned short u16;

typedef struct {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
} Rec;

extern int TP_GetLatestIndexInAuto(void);
extern void TP_GetCalibratedPoint(Rec *out, Rec *in);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern Rec data_02060534[];

int CopyRecentInputRecords(Rec *table) {
    int bank;
    int i;
    short count = 0;

    if (!((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15)) {
        Rec buf;

        bank = TP_GetLatestIndexInAuto();
        i = 0;
        bank -= 3;

        for (; i < 4; i++) {
            int idx = bank + i;
            if (idx < 0) {
                idx += 5;
            }
            TP_GetCalibratedPoint(&buf, &data_02060534[idx]);
            MI_CpuCopy8(&buf, &table[count++], 8);
        }
    }

    return count;
}
