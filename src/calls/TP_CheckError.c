extern int data_02059784;

int TP_CheckError(int arg0) {
    return *(unsigned short *)((char *)&data_02059784 + 0x38) & arg0;
}
