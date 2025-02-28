#pragma once
#include <stdint.h>

#define VIDEO_RAM_SIZE 0x1FFF
#define NUMBER_OF_PIXELS 100	

typedef struct
{
	uint8_t data[16];
}tile;

typedef struct Gpu
{
	tile tile_set[384];
	uint8_t video_ram[VIDEO_RAM_SIZE];
	uint8_t canvas_buffer[NUMBER_OF_PIXELS];
}gpu, *gptr;