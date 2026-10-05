extern int data_02060388;

void SetDisplaySetting(int value) {
    if (*(int *)((char *)&data_02060388 + 4) == 0 || value == 0) {
        *(int *)((char *)&data_02060388 + 8) = value;
    }
}
