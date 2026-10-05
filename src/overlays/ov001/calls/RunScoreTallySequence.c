#include "nitro/types.h"

typedef struct Point {
    s32 x;
    s32 y;
} Point;

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    s32 startTick[2];
    TweenFlags flags;
} Tween;

typedef struct Sprite {
    u8 data[0xc];
} Sprite;

typedef struct FadeNode {
    u8 pad_00[0xa4];
    s32 scale;
} FadeNode;

typedef struct PartyInfo {
    u8 pad_00[2];
    u16 bonus;
} PartyInfo;

typedef struct PartyEntry {
    u8 pad_000[0x1d4];
    PartyInfo *info;
} PartyEntry;

typedef struct ScoreTally {
    u32 pad_000;
    s32 active;
    u8 pad_008[0x34 - 0x08];
    Sprite digits[10];
    u8 pad_0ac[0xc4 - 0xac];
    Sprite separator;
    u8 pad_0d0[0x10c - 0xd0];
    s32 state;
    s32 count;
    u8 pad_114[0x140 - 0x114];
    u8 flags;
    u8 pad_141[0x160 - 0x141];
    s32 score;
    u8 pad_164[0x19c - 0x164];
    Tween tween;
    u8 pad_1b8[0x2bc - 0x1b8];
    FadeNode node;
    u8 pad_364[0x3c0 - 0x364];
    Sprite bonusLabel;
    Sprite timeLabel;
} ScoreTally;

extern u16 data_02060500;
extern Point data_ov001_0209dfbc;

extern void StartTimerFromPackedPair(Tween *tween, u32 packed, int duration);
extern void PlaySoundChecked(void *ptr, int arg);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern PartyEntry *GetBoundedEntryField(int index);
extern void AddSessionCounter(int index, int amount);
extern void StopSeqArcOrDefault(int seqArcNo, int seqIndex, int fadeFrames);
extern void func_02052528(Tween *tween, int mode, int from, int to, int duration);
extern void func_02052570(Tween *tween);
extern u32 func_ov001_02063b68(s32 index);
extern int func_ov001_02064784(void);
extern u32 GetClampedTimerValue(void);
extern void func_ov001_02063d4c(int parameterId, int value);
extern void func_ov001_0207ca2c(Point *pos, s32 scale, Sprite *sprite, s32 color);
extern s32 DigitCount(s32 value);
extern s32 IntPow(s32 base, s32 exponent);
extern void func_ov001_0207c988(void);
extern void func_01ffb12c(FadeNode *node);

void RunScoreTallySequence(ScoreTally *tally)
{
    Tween *tween = &tally->tween;
    FadeNode *node = &tally->node;
    BOOL skipped = FALSE;
    BOOL showBonus = FALSE;
    BOOL showTime = FALSE;
    Point pos;
    s32 digitCount;
    s32 value;
    s32 divisor;
    s32 i;

    switch (tally->state) {
    case 0:
        StartTimerFromPackedPair(tween, 0x20000, 500);
        PlaySoundChecked(0, 0xc);
        tally->state = 1;
    case 1:
        SampleTweenValue(tween, &node->scale);
        if (!tween->flags.finished) {
            break;
        }
        StartTimerFromPackedPair(tween, 0, 1000);
        tally->state = 2;
    case 2:
        SampleTweenValue(tween, &node->scale);
        if (!tween->flags.finished) {
            break;
        }
        tally->count = GetBoundedEntryField(0)->info->bonus;
        PlaySoundChecked(0, 0x39);
        tally->state = 3;
    case 3:
        showBonus = TRUE;
        if (data_02060500 & 0x2f0f) {
            AddSessionCounter(0, tally->count * 100);
            tally->count = 0;
            skipped = TRUE;
        }
        if (tally->count > 0) {
            tally->count--;
            AddSessionCounter(0, 100);
        } else {
            int duration = 0;

            StopSeqArcOrDefault(0, 0x39, 0);
            if (!skipped) {
                duration = 0x1000;
            }
            func_02052528(tween, 0, 0, duration, 250);
            func_02052570(tween);
            tally->state = 4;
        }
        tally->score = func_ov001_02063b68(0);
        if (tally->score > 999999) {
            tally->score = 999999;
        }
        break;
    case 4:
        showBonus = TRUE;
        SampleTweenValue(tween, NULL);
        if (!tween->flags.finished) {
            break;
        }
        if (func_ov001_02064784() == 6) {
            tally->count = GetClampedTimerValue() / 10;
            if (tally->count > 0) {
                PlaySoundChecked(0, 0x39);
            }
            showBonus = FALSE;
            showTime = TRUE;
            tally->state = 5;
        } else {
            tally->state = 6;
        }
        break;
    case 5:
        tally->flags |= 0x20;
        showTime = TRUE;
        if (data_02060500 & 0x2f0f) {
            AddSessionCounter(0, tally->count);
            func_ov001_02063d4c(5, -tally->count * 10);
            tally->count = 0;
            skipped = TRUE;
        }
        if (tally->count > 0) {
            s32 step = tally->count;

            if (step >= 100) {
                step = step % 100 + 100;
            }
            tally->count -= step;
            AddSessionCounter(0, step);
            func_ov001_02063d4c(5, -step * 10);
        } else {
            int duration = 0;

            StopSeqArcOrDefault(0, 0x39, 0);
            if (!skipped) {
                duration = 0x1000;
            }
            func_02052528(tween, 0, 0, duration, 250);
            func_02052570(tween);
            tally->state = 6;
        }
        tally->score = func_ov001_02063b68(0);
        if (tally->score > 999999) {
            tally->score = 999999;
        }
        break;
    case 6:
        if (func_ov001_02064784() != 6) {
            showBonus = TRUE;
        } else {
            showTime = TRUE;
            tally->flags |= 0x10;
        }
        if (data_02060500 & 0x2f0f) {
            tally->state = 7;
            tally->active = 0;
        }
        break;
    }

    if (tally->state == 7) {
        return;
    }
    pos = data_ov001_0209dfbc;
    if (showBonus) {
        func_ov001_0207ca2c(&pos, 0x1000, &tally->bonusLabel, 0x7fff);
        value = tally->count * 100;
        digitCount = DigitCount(value);
        pos.x += 0x20000;
    } else if (showTime) {
        func_ov001_0207ca2c(&pos, 0x1000, &tally->timeLabel, 0x7fff);
        value = tally->count;
        digitCount = DigitCount(value);
        pos.x += 0x2d000;
    }
    if (showBonus || showTime) {
        pos.x = 0xc000;
        pos.y += 0xc000;
        func_ov001_0207ca2c(&pos, 0x1000, &tally->separator, 0x7fff);
        divisor = IntPow(10, digitCount - 1);
        for (i = 0; i < digitCount; i++) {
            pos.x += 0xd000;
            func_ov001_0207ca2c(&pos, 0x1000, &tally->digits[value / divisor], 0x7fff);
            value %= divisor;
            divisor /= 10;
        }
    }
    func_ov001_0207c988();
    func_01ffb12c(node);
}
