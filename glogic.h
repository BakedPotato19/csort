#include <bits/stdint-uintn.h>
#include <stdint.h>
#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

struct Board
{
	uint32_t* state;
	uint8_t pipes;
};

/*
 * Define ball colors
 */
enum colors{Empty, Brown, Lightgreen, Darkblue, Grey, Darkgreen, Red, Pink,
			Green, Lightblue, Orange, Purple, Yellow};
;


bool emptyPipe(uint32_t pipe);
bool filledPipe(uint32_t pipe);
uint8_t ballAtIndex(uint32_t pipe, uint8_t index); 
uint8_t pipeSpot(uint32_t pipe);

bool move(uint32_t *pipe1, uint32_t *pipe2);
uint32_t craftPipe(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
bool boardPrint(struct Board* b);

struct Board *SBoard_deep_cpy(struct Board *orig);

bool solved(struct Board* b);

bool freeSBoard(struct Board* b);

bool move_is_valid(uint32_t giver, uint32_t reciever);


