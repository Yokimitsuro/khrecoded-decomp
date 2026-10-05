#include "nitro/types.h"

extern s8 func_ov001_02068084(void);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern u32 ReadSessionPackedBits(int flagIndex, u32 bitCount);
extern void WriteSessionPackedBits(int flagIndex, u32 bitCount, u32 value);
extern BOOL func_ov001_020645c8(u32 flagIndex);
extern void func_ov001_020645dc(int flagIndex);
extern void func_ov001_020645e8(int flagIndex);

void CommitChapterClearRecords(void)
{
    int chapter;
    int clearCount;
    int bestCount;
    u32 clearTime;
    u32 bestTime;

    chapter = func_ov001_02068084();
    if (ReadGlobalPackedBits(0x1a00, 2) == 0) {
        if (chapter == 7 && IsGlobalPackedBitSet(0xbea) != 0) {
            return;
        }
        func_ov001_020645dc(chapter + 0xa0b);
        WriteSessionPackedBits(0xf38, 4, chapter + 1);
    }
    if (ReadGlobalPackedBits(0x1a00, 2) != 3) {
        if (func_ov001_020645c8(0x35c9) != 0) {
            func_ov001_020645dc(chapter + 0xa23);
        }
        if (func_ov001_020645c8(0x35ca) != 0) {
            func_ov001_020645dc(chapter + 0xa63);
        }
        if (ReadSessionPackedBits(0x35c7, 2) == 1) {
            func_ov001_020645dc(chapter + 0x12b8);
        }
        if (ReadSessionPackedBits(0x35c7, 2) == 2) {
            func_ov001_020645dc(chapter + 0xa13);
        }
        if (ReadSessionPackedBits(0x35c7, 2) == 3) {
            func_ov001_020645dc(chapter + 0xa1b);
        }
        clearCount = ReadSessionPackedBits(0x35cb, 7);
        bestCount = ReadSessionPackedBits(chapter * 7 + 0xa2b, 7);
        if (bestCount == 0 || clearCount < bestCount) {
            if (clearCount > 99) {
                clearCount = 99;
            }
            WriteSessionPackedBits(chapter * 7 + 0xa2b, 7, clearCount);
        }
        clearTime = ReadSessionPackedBits(0x35d2, 17);
        bestTime = ReadSessionPackedBits(chapter * 17 + 0xa6b, 17);
        if (bestTime == 0 || clearTime < bestTime) {
            if (clearTime > 99999) {
                clearTime = 99999;
            }
            WriteSessionPackedBits(chapter * 17 + 0xa6b, 17, clearTime);
        }
    }
    if (chapter != 7 || ReadGlobalPackedBits(0x1a00, 2) != 0) {
        func_ov001_020645e8(0x3536);
    }
}
