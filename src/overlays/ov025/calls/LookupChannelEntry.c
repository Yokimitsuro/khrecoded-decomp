extern int data_ov025_020b7780;
extern int GetSlotEntryValue_020b7608();

int LookupChannelEntry(int arg0) {
    return GetSlotEntryValue_020b7608(*(int *)&data_ov025_020b7780 + 25844, arg0);
}
