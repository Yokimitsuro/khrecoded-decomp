#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptValue {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptValue;

typedef struct ScriptContext {
    u8 pad_000[0x218];
    ScriptValue stack[1];
} ScriptContext;

#define SCRIPT_FIXED 0x10
#define SCRIPT_INT 1

extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);
extern ScriptValue *ScriptVm_ResolveOperand(ScriptContext *ctx, u16 *operand);
extern fx32 ScriptValue_ToScalar(ScriptValue *value);
extern s32 GetField4UnlessState2(ScriptValue *value);
extern fx32 FX_Mul(fx32 left, fx32 right);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern s32 _s32_div_f(s32 numerator, s32 denominator);

#define BINARY_CMP(OP)                                                   \
    {                                                                    \
        ScriptValue *right = &ctx->stack[depth - 1];                     \
        ScriptValue *left = &ctx->stack[depth - 2];                      \
                                                                         \
        if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) { \
            fx32 x = ScriptValue_ToScalar(left);                                \
                                                                         \
            left->value = (x OP ScriptValue_ToScalar(right)) ? 1 : 0;           \
            left->type = SCRIPT_INT;                                     \
        } else {                                                         \
            s32 x = GetField4UnlessState2(left);                \
                                                                         \
            left->value = (x OP GetField4UnlessState2(right)) ? 1 : 0; \
            left->type = SCRIPT_INT;                                     \
        }                                                                \
        depth--;                                                         \
    }

ScriptValue *ScriptVm_EvalExpr(ScriptContext *ctx, u16 *code)
{
    int depth = 0;

    while (*code != 0xf) {
        switch (*(volatile u16 *)code) {
        case 0: {
            u16 operand[4];

            MIi_CpuCopy16(code + 1, operand, sizeof(operand));
            ctx->stack[depth] = *ScriptVm_ResolveOperand(ctx, operand);
            depth++;
            code += 4;
            break;
        }
        case 1: {
            ScriptValue *top = &ctx->stack[depth - 1];

            top->value = -top->value;
            break;
        }
        case 2: {
            ScriptValue *top = &ctx->stack[depth - 1];

            top->value = top->value == 0 ? 1 : 0;
            break;
        }
        case 3: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) {
                fx32 x = ScriptValue_ToScalar(left);

                /* Shipped code adds the left operand to itself. */
                left->value = x + ScriptValue_ToScalar(left);
                left->type = SCRIPT_FIXED;
            } else {
                s32 x = GetField4UnlessState2(left);

                left->value = x + GetField4UnlessState2(right);
                left->type = SCRIPT_INT;
            }
            depth--;
            break;
        }
        case 4: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) {
                fx32 x = ScriptValue_ToScalar(left);

                left->value = x - ScriptValue_ToScalar(right);
                left->type = SCRIPT_FIXED;
            } else {
                s32 x = GetField4UnlessState2(left);

                left->value = x - GetField4UnlessState2(right);
                left->type = SCRIPT_INT;
            }
            depth--;
            break;
        }
        case 5: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) {
                fx32 x = ScriptValue_ToScalar(left);

                left->value = FX_Mul(x, ScriptValue_ToScalar(right));
                left->type = SCRIPT_FIXED;
            } else {
                s32 x = GetField4UnlessState2(left);

                left->value = x * GetField4UnlessState2(right);
                left->type = SCRIPT_INT;
            }
            depth--;
            break;
        }
        case 6: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            if (left->type == SCRIPT_FIXED || right->type == SCRIPT_FIXED) {
                fx32 x = ScriptValue_ToScalar(left);

                left->value = FX_Div(x, ScriptValue_ToScalar(right));
                left->type = SCRIPT_FIXED;
            } else {
                s32 x = GetField4UnlessState2(left);

                left->value = _s32_div_f(x, GetField4UnlessState2(right));
                left->type = SCRIPT_INT;
            }
            depth--;
            break;
        }
        case 7:
            BINARY_CMP(==)
            break;
        case 8:
            BINARY_CMP(>)
            break;
        case 9:
            BINARY_CMP(<)
            break;
        case 10:
            BINARY_CMP(>=)
            break;
        case 11:
            BINARY_CMP(<=)
            break;
        case 12:
            BINARY_CMP(!=)
            break;
        case 13: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            left->value = (left->value != 0 && right->value != 0) ? 1 : 0;
            depth--;
            break;
        }
        case 14: {
            ScriptValue *right = &ctx->stack[depth - 1];
            ScriptValue *left = &ctx->stack[depth - 2];

            left->value = (left->value != 0 || right->value != 0) ? 1 : 0;
            depth--;
            break;
        }
        }
        code++;
    }
    return &ctx->stack[depth - 1];
}
