#define HAS_ZERO_BYTE_MASK 0x80808080
#define HAS_ZERO_BYTE_BIAS 0xfefefeff

int strcmp(const char *first, const char *second)
{
    register unsigned char *left = (unsigned char *)first;
    register unsigned char *right = (unsigned char *)second;
    unsigned long alignment;
    unsigned long leftWord;
    unsigned long rightWord;
    unsigned long zeroTest;

    leftWord = *left;
    rightWord = *right;
    if (leftWord - rightWord) {
        return leftWord - rightWord;
    }

    if ((alignment = ((int)left & 3)) != ((int)right & 3)) {
        goto compare_bytes;
    }
    if (alignment) {
        if (leftWord == 0) {
            return 0;
        }
        for (alignment = 3 - alignment; alignment; alignment--) {
            leftWord = *(++left);
            rightWord = *(++right);
            if (leftWord - rightWord) {
                return leftWord - rightWord;
            }
            if (leftWord == 0) {
                return 0;
            }
        }
        left++;
        right++;
    }

    leftWord = *(int *)left;
    rightWord = *(int *)right;
    zeroTest = leftWord + HAS_ZERO_BYTE_BIAS;
    if (zeroTest & ~leftWord & HAS_ZERO_BYTE_MASK) {
        goto adjust;
    }

    while (leftWord == rightWord) {
        leftWord = *(++((int *)left));
        rightWord = *(++((int *)right));
        zeroTest = leftWord + HAS_ZERO_BYTE_BIAS;
        if (zeroTest & HAS_ZERO_BYTE_MASK) {
            goto adjust;
        }
    }

    --left;
    --right;
    goto compare_bytes;

adjust:
    leftWord = *left;
    rightWord = *right;
    if (leftWord - rightWord) {
        return leftWord - rightWord;
    }

compare_bytes:
    if (leftWord == 0) {
        return 0;
    }
    do {
        leftWord = *(++left);
        rightWord = *(++right);
        if (leftWord - rightWord) {
            return leftWord - rightWord;
        }
    } while (leftWord != 0);
    return 0;
}
