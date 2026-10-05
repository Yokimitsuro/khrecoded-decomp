/* Independent reconstruction from Ghidra caller evidence and ARM9 instruction bytes. */
typedef struct {
    unsigned char overlaySet;
    unsigned char unknown_001[0x143];
} OverlaySelectionRecord;

extern OverlaySelectionRecord data_02060b50[];

OverlaySelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex) {
    return &data_02060b50[selectionIndex];
}
