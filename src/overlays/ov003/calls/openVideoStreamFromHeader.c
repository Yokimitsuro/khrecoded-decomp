extern void func_ov003_02064864(int streamContext, unsigned short *dst, unsigned short *sourceHeader);
extern void InitTextLayerDefault(unsigned int *streamContext, int streamOption, unsigned int streamFlags, unsigned short *preparedHeader);

void openVideoStreamFromHeader(unsigned int *streamContext, int streamOption, unsigned int streamFlags, unsigned short *sourceHeader) {
    unsigned short preparedHeader[8];
    func_ov003_02064864((int)streamContext, preparedHeader, sourceHeader);
    InitTextLayerDefault(streamContext, streamOption, streamFlags, preparedHeader);
}
