extern int *cardi_common;

int CARD_GetResultCode(void) {
    return *cardi_common;
}
