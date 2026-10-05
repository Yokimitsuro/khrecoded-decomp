extern void G2x_SetBlendAlpha_(unsigned int reg, int unknownMode0, int unknownMode1, int unknownMode2, int unknownMode3);

void set_engine_alpha_blend(char *object, int blendAlpha) {
    if (*(int *)(object + 0x4604) == 2)
        G2x_SetBlendAlpha_(0x04001050, 0, blendAlpha, 0x10, 0);
    else
        G2x_SetBlendAlpha_(0x04000050, 0, blendAlpha, 0x10, 0);
}
