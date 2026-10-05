extern void InitMovieStreamFromHeader_020a8954(int streamContext, unsigned short *dst, unsigned short *sourceHeader);
extern void InitTextLayerDefault(unsigned int *streamContext, int streamOption, unsigned int streamFlags, unsigned short *preparedHeader);

void openVideoStreamFromHeader_020a8a24(unsigned int *streamContext, int streamOption, unsigned int streamFlags, unsigned short *sourceHeader) {
    unsigned short preparedHeader[8];
    InitMovieStreamFromHeader_020a8954((int)streamContext, preparedHeader, sourceHeader);
    InitTextLayerDefault(streamContext, streamOption, streamFlags, preparedHeader);
}
