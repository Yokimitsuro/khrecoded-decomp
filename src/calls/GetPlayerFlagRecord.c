extern int data_020608e0;

int GetPlayerFlagRecord(int arg0) {
    return (int)&data_020608e0 + arg0 * 12;
}
