extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);

struct SmallRecord {
    int field0;
    int field4;
    int field8;
    int fieldC;
    char _10[8];
    unsigned int flags;
};

void func_02052528(struct SmallRecord *record, int value0, int value1, int value2, int value3) {
    MI_CpuFill8(record, 0, 0x1c);
    record->field0 = value0;
    record->field8 = value1;
    record->fieldC = value2;
    record->field4 = value3;
    record->flags &= ~1;
    record->flags &= ~2;
    record->flags &= ~4;
}
