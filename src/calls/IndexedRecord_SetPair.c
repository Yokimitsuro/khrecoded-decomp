struct TwoWordValue {
    int first;
    int second;
};

struct IndexedRecord {
    char pad0[0x10];
    struct TwoWordValue value;
    char pad1[0x8c - 0x18];
};

void IndexedRecord_SetPair(struct IndexedRecord *recordBase, int recordIndex, struct TwoWordValue *sourceValue) {
    if (recordIndex < 0) return;
    recordBase[recordIndex].value = *sourceValue;
}
