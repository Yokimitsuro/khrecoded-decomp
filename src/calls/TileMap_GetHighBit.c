unsigned int TileMap_GetHighBit(unsigned int packed_coordinate) {
    unsigned int coordinate_mask = 0xfffffc;
    unsigned int map_row_address = (packed_coordinate >> 7 & coordinate_mask) + 0x1ff8000;
    unsigned short local_tile_index = packed_coordinate & (coordinate_mask >> 15);
    int row_header = *(unsigned short *)(map_row_address + 2) & (coordinate_mask >> 15);

    return *(unsigned int *)(map_row_address + ((unsigned int)(((row_header + 1) / 2) << 0x11) >> 0xf)
                                  + local_tile_index * 4 + 0x10) & 0x80000000;
}
