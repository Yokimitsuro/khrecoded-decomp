#include "nitro/types.h"

typedef char *VaList;
#define VA_SLOT_SIZE(type) ((sizeof(type) + 3U) & ~3U)
#define VA_ARG(args, type) (*(type *)(((args) += VA_SLOT_SIZE(type)) - VA_SLOT_SIZE(type)))

typedef struct WideTextSink {
    u32 remaining;
    u16 *cursor;
    u16 *start;
} WideTextSink;

enum {
    FORMAT_BLANK = 0x1,
    FORMAT_PLUS = 0x2,
    FORMAT_ALTERNATE = 0x4,
    FORMAT_LEFT_ALIGN = 0x8,
    FORMAT_ZERO_PAD = 0x10,
    FORMAT_LONG = 0x20,
    FORMAT_SHORT = 0x40,
    FORMAT_LONG_LONG = 0x80,
    FORMAT_CHAR = 0x100,
    FORMAT_UNSIGNED = 0x1000
};

extern void PrintfDestWide_PutChar(WideTextSink *sink, u16 character);
extern void FillWideBuffer(WideTextSink *sink, u16 fillChar, int count);
extern void CopyIntoWideBuffer(WideTextSink *sink, const u16 *text, int count);
extern void Fx64_FormatWide(s64 value, int precision, u16 *intText, u16 *fracText);
extern u32 Utf16Length(const u16 *text);
extern u32 _u32_div_f(u32 dividend, u32 divisor);
extern u64 _ll_udiv(u64 dividend, u64 divisor);
extern s64 _ll_mul(s64 left, s64 right);

/* Wide-character vsnprintf with fixed-point %f support. */
int Text_VSNPrintfWide(u16 *dest, u32 destLength, const u16 *format, VaList args)
{
    u16 digits[24];
    u16 fracText[14];
    int digitCount;
    u16 prefix[2];
    int prefixCount;

    const u16 *cursor = format;

    WideTextSink sink;
    sink.remaining = destLength, sink.cursor = sink.start = dest;

    while (*cursor) {
        if (*cursor != '%') {
            PrintfDestWide_PutChar(&sink, *cursor++);
        } else {
            int flags = 0, width = 0, precision = -1, radix = 10;
            char hexBase = 'a' - 10;
            const u16 *specStart = cursor;

            for (;;) {
                switch (*++cursor) {
                case '+':
                    flags |= FORMAT_PLUS;
                    continue;
                case ' ':
                    flags |= FORMAT_BLANK;
                    continue;
                case '-':
                    flags |= FORMAT_LEFT_ALIGN;
                    continue;
                case '0':
                    flags |= FORMAT_ZERO_PAD;
                    continue;
                }
                break;
            }

            if (*cursor == '*') {
                ++cursor, width = VA_ARG(args, int);
                if (width < 0)
                    width = -width, flags |= FORMAT_LEFT_ALIGN;
            } else {
                while ((*cursor >= '0') && (*cursor <= '9'))
                    width = (width * 10) + *cursor++ - '0';
            }

            if (*cursor == '.') {
                ++cursor, precision = 0;
                if (*cursor == '*') {
                    ++cursor, precision = VA_ARG(args, int);
                    if (precision < 0)
                        precision = -1;
                } else {
                    while ((*cursor >= '0') && (*cursor <= '9'))
                        precision = (precision * 10) + *cursor++ - '0';
                }
            }

            switch (*cursor) {
            case 'h':
                if (*++cursor != 'h')
                    flags |= FORMAT_SHORT;
                else
                    ++cursor, flags |= FORMAT_CHAR;
                break;
            case 'l':
                if (*++cursor != 'l')
                    flags |= FORMAT_LONG;
                else
                    ++cursor, flags |= FORMAT_LONG_LONG;
                break;
            }

            switch (*cursor) {
            case 'd':
            case 'i':
                goto put_integer;
            case 'o':
                radix = 8;
                flags |= FORMAT_UNSIGNED;
                goto put_integer;
            case 'u':
                flags |= FORMAT_UNSIGNED;
                goto put_integer;
            case 'X':
                hexBase = 'A' - 10;
                goto put_hexadecimal;
            case 'x':
                goto put_hexadecimal;
            case 'p':
                flags |= FORMAT_ALTERNATE;
                precision = 8;
                goto put_hexadecimal;
            case 'c':
                if (precision >= 0)
                    goto put_invalid;
                {
                    int character = VA_ARG(args, int);
                    width -= 1;
                    if (flags & FORMAT_LEFT_ALIGN) {
                        PrintfDestWide_PutChar(&sink, (u16)character);
                        FillWideBuffer(&sink, ' ', width);
                    } else {
                        u16 padChar = (u16)((flags & FORMAT_ZERO_PAD) ? L'0' : L' ');
                        FillWideBuffer(&sink, padChar, width);
                        PrintfDestWide_PutChar(&sink, (u16)character);
                    }
                    ++cursor;
                }
                break;
            case 's':
            {
                int length = 0;
                const u16 *text = VA_ARG(args, const u16 *);
                if (precision < 0) {
                    while (text[length])
                        ++length;
                } else {
                    while ((length < precision) && text[length])
                        ++length;
                }
                width -= length;
                if (flags & FORMAT_LEFT_ALIGN) {
                    CopyIntoWideBuffer(&sink, text, length);
                    FillWideBuffer(&sink, ' ', width);
                } else {
                    char padChar = (char)(u16)((flags & FORMAT_ZERO_PAD) ? L'0' : L' ');
                    FillWideBuffer(&sink, padChar, width);
                    CopyIntoWideBuffer(&sink, text, length);
                }
                ++cursor;
            }
            break;
            case 'n':
            {
                int byteCount = (char *)sink.cursor - (char *)sink.start;
                if (flags & FORMAT_CHAR)
                    ;
                else if (flags & FORMAT_SHORT)
                    *VA_ARG(args, s16 *) = (s16)byteCount;
                else if (flags & FORMAT_LONG_LONG)
                    *VA_ARG(args, u64 *) = (u64)byteCount;
                else
                    *VA_ARG(args, int *) = byteCount;
            }
                ++cursor;
                break;
            case '%':
                if (specStart + 1 != cursor)
                    goto put_invalid;
                PrintfDestWide_PutChar(&sink, *cursor++);
                break;
            default:
                goto put_invalid;
put_invalid:
                CopyIntoWideBuffer(&sink, specStart, cursor - specStart);
                break;
            case 'f':
            {
                s64 value;

                prefixCount = 0;
                if (precision < 0)
                    precision = 6;
                if (precision > 8)
                    precision = 8;
                if (flags & (FORMAT_LONG | FORMAT_LONG_LONG))
                    value = VA_ARG(args, s64);
                else
                    value = VA_ARG(args, long);
                if ((value >> 32) & 0x80000000) {
                    value = ~value + 1;
                    prefix[0] = '-';
                    prefixCount = 1;
                } else if (flags & FORMAT_PLUS) {
                    prefix[0] = '+';
                    prefixCount = 1;
                } else if (flags & FORMAT_BLANK) {
                    prefix[0] = ' ';
                    prefixCount = 1;
                }
                Fx64_FormatWide(value, precision, digits, fracText);
                if (prefixCount + (Utf16Length(digits) + Utf16Length(fracText)) + 1 < width)
                    FillWideBuffer(&sink, ' ', width - (prefixCount + (Utf16Length(digits) + Utf16Length(fracText)) + 1));
                if (prefixCount > 0)
                    PrintfDestWide_PutChar(&sink, prefix[0]);
                CopyIntoWideBuffer(&sink, digits, Utf16Length(digits));
                if (fracText[0] != 0) {
                    PrintfDestWide_PutChar(&sink, '.');
                    CopyIntoWideBuffer(&sink, fracText, Utf16Length(fracText));
                }
                ++cursor;
            }
            break;
put_hexadecimal:
                radix = 16;
                flags |= FORMAT_UNSIGNED;
put_integer:
                {
                    u64 value = 0;
                    prefixCount = 0;

                    if (flags & FORMAT_LEFT_ALIGN)
                        flags &= ~FORMAT_ZERO_PAD;
                    if (precision < 0)
                        precision = 1;
                    else
                        flags &= ~FORMAT_ZERO_PAD;

                    if (flags & FORMAT_UNSIGNED) {
                        if (flags & FORMAT_CHAR)
                            value = VA_ARG(args, u8);
                        else if (flags & FORMAT_SHORT)
                            value = VA_ARG(args, u16);
                        else if (flags & FORMAT_LONG_LONG)
                            value = VA_ARG(args, u64);
                        else
                            value = VA_ARG(args, unsigned long);
                        flags &= ~(FORMAT_PLUS | FORMAT_BLANK);
                        if (flags & FORMAT_ALTERNATE) {
                            if (radix == 16) {
                                if (value != 0) {
                                    prefix[0] = (char)(hexBase + (10 + 'x' - 'a'));
                                    prefix[1] = '0';
                                    prefixCount = 2;
                                }
                            } else if (radix == 8) {
                                prefix[0] = '0';
                                prefixCount = 1;
                            }
                        }
                    } else {
                        if (flags & FORMAT_CHAR)
                            value = VA_ARG(args, char);
                        else if (flags & FORMAT_SHORT)
                            value = VA_ARG(args, short);
                        else if (flags & FORMAT_LONG_LONG)
                            value = VA_ARG(args, u64);
                        else
                            value = VA_ARG(args, long);
                        if ((value >> 32) & 0x80000000) {
                            value = ~value + 1;
                            prefix[0] = '-';
                            prefixCount = 1;
                        } else {
                            if (value || precision) {
                                if (flags & FORMAT_PLUS) {
                                    prefix[0] = '+';
                                    prefixCount = 1;
                                } else if (flags & FORMAT_BLANK) {
                                    prefix[0] = ' ';
                                    prefixCount = 1;
                                }
                            }
                        }
                    }
                    digitCount = 0;
                    switch (radix) {
                    case 8:
                        while (value != 0) {
                            int digit = (int)(value & 0x07);
                            value >>= 3;
                            digits[digitCount++] = (u16)(digit + '0');
                        }
                        break;
                    case 10:
                        if ((value >> 32) == 0) {
                            u32 low = (u32)value;
                            while (low != 0) {
                                u32 quotient = _u32_div_f(low, 10);
                                int digit = (int)(low - (quotient * 10));
                                low = quotient;
                                digits[digitCount++] = (u16)(digit + '0');
                            }
                        } else {
                            while (value != 0) {
                                s64 quotient = _ll_udiv(value, 10);
                                int digit = (int)(value - _ll_mul(quotient, 10));
                                value = quotient;
                                digits[digitCount++] = (u16)(digit + '0');
                            }
                        }
                        break;
                    case 16:
                        while (value != 0) {
                            int digit = (int)(value & 0x0f);
                            value >>= 4;
                            digits[digitCount++] = (u16)((digit < 10) ? (digit + '0') : (digit + hexBase));
                        }
                        break;
                    }
                    if ((prefixCount > 0) && (prefix[0] == '0')) {
                        prefixCount = 0;
                        digits[digitCount++] = '0';
                    }
                }
                {
                    int zeroPad = precision - digitCount;
                    if (flags & FORMAT_ZERO_PAD) {
                        if (zeroPad < width - digitCount - prefixCount)
                            zeroPad = width - digitCount - prefixCount;
                    }
                    if (zeroPad > 0)
                        width -= zeroPad;
                    width -= prefixCount + digitCount;
                    if (!(flags & FORMAT_LEFT_ALIGN))
                        FillWideBuffer(&sink, ' ', width);
                    while (prefixCount > 0)
                        PrintfDestWide_PutChar(&sink, prefix[--prefixCount]);
                    FillWideBuffer(&sink, '0', zeroPad);
                    while (digitCount > 0)
                        PrintfDestWide_PutChar(&sink, digits[--digitCount]);
                    if (flags & FORMAT_LEFT_ALIGN)
                        FillWideBuffer(&sink, ' ', width);
                    ++cursor;
                }
                break;
            }
        }
    }

    if (sink.remaining > 0) {
        *sink.cursor = '\0';
    } else if (destLength > 0) {
        *(sink.start + destLength - 1) = '\0';
    }

    return sink.cursor - sink.start;
}
