typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration_ticks;
    s32 from;
    s32 to;
    long long startTick;
    TweenFlags flags;
} Tween;

extern long long OS_GetTick(void);
extern int _ll_udiv(u64 output_value, u32 divisor, int mode);
extern s32 TweenValue(s32 start, s32 end, u32 elapsed_ticks, u32 duration_ticks, u32 curve);

void SampleTweenValue(Tween *tween_state, s32 *output_value)
{
    u32 elapsed_ticks;

    if (!tween_state->flags.started) {
        return;
    }

    if (!tween_state->flags.finished) {
        u32 duration_ticks;

        if (!tween_state->flags.paused) {
            elapsed_ticks = _ll_udiv(
                (u64)(OS_GetTick() - tween_state->startTick) << 6, 0x82ea, 0);
        } else {
            elapsed_ticks = _ll_udiv((u64)tween_state->startTick << 6, 0x82ea, 0);
        }
        duration_ticks = tween_state->duration_ticks;
        if (elapsed_ticks >= duration_ticks) {
            tween_state->flags.finished = 1;
            elapsed_ticks = duration_ticks;
        }
    } else {
        elapsed_ticks = tween_state->duration_ticks;
    }

    if (output_value != 0) {
        *output_value = TweenValue(tween_state->from, tween_state->to, elapsed_ticks, tween_state->duration_ticks,
                                tween_state->mode);
    }
}
