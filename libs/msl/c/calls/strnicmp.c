extern const unsigned char sLowerCaseMap[128];

int strnicmp(const char *left, const char *right, int maxLength)
{
    int index;
    int leftCharacter;
    int rightCharacter;
    unsigned char leftLower;
    unsigned char rightLower;

    for (index = 0; index < maxLength; index++) {
        leftCharacter = *(const unsigned char *)left++;
        leftLower = leftCharacter < 0 || leftCharacter >= 0x80
            ? leftCharacter
            : sLowerCaseMap[leftCharacter];
        rightCharacter = *(const unsigned char *)right++;
        rightLower = rightCharacter < 0 || rightCharacter >= 0x80
            ? rightCharacter
            : sLowerCaseMap[rightCharacter];

        if (leftLower < rightLower) {
            return -1;
        }
        if (leftLower > rightLower) {
            return 1;
        }
        if (leftLower == 0) {
            return 0;
        }
    }
    return 0;
}
