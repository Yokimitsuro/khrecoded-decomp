/* CARD_GetBackupSectorSize: backup sector size from the card context (+0x1c). */

extern int *data_ov037_020bb780;

int CARD_GetBackupSectorSize(void) {
    return *(int *)((char *)data_ov037_020bb780 + 0x1c);
}
