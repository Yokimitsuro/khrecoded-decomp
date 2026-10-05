struct IndexedRecord { char pad[0x7c]; int flags; char pad2[0x8c - 0x80]; };

void IndexedRecord_ClearActive(struct IndexedRecord *recordBase, int recordIndex)
{
    if (recordIndex < 0) return;
    recordBase[recordIndex].flags &= ~2;
}
