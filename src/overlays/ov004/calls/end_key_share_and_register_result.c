extern int PXI_Init_0204f0c8();
extern void Slot_SetMode2Bit();
extern void IndexedRecords_SetFlag2();

int end_key_share_and_register_result(int context, int argument) {
    int resultObject = PXI_Init_0204f0c8(context, argument, 0);
    Slot_SetMode2Bit(context, resultObject, 0);
    IndexedRecords_SetFlag2(context, resultObject, 0);
    return resultObject;
}
