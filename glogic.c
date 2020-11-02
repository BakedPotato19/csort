#include "glogic.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//=====================================================
// Section for implementation of the game BallSort
//
//=====================================================


/*
 * The board consist of x pipes.
 * Each pipe can store up to 4 balls
 * Balls have x-2 different colors. (All boards start with two free pipes)
 * As each pipe can store 4 balls it is implement it uint32_t, preserving
 * 8 bits for each pipe. 0x00 is empty, so the uint32_t solution supports
 * up to x=255 balls.
 *
 * */


/*
 * Pipe indexing tools
 */

uint32_t indexes[] = {0x00FFFFFF,0xFF00FFFF,0xFFFF00FF,0xFFFFFF00};



/*
 * This function appends 4x 8bit ints to a 32 bit int;
 * appending the bit sequence of b to a, c to ba etc.
 * */

bool emptyPipe(uint32_t pipe)
{
	return !pipe;
}

bool filledPipe(uint32_t pipe)
{
	return ((pipe<<24)>>24);
}

/*
 * Returns ball at index as uint8_t.
 * 0 is bottom; 3 is top
 */
uint8_t ballAtIndex(uint32_t pipe, uint8_t index)
{
	return (pipe<<(index*8))>>24;
}

/*
 * Returns index of top ball
 * return 4 on error.
 */
uint8_t pipeSpot(uint32_t pipe)
{
	uint8_t spot = 4;
	for(uint8_t i = 4; i>=1; i--)
	{
		uint32_t ball = (pipe<<((i-1)*8))>>24;
		if(!ball) spot = i-1;
	}

	return spot;
}

uint8_t clearAtIndex(uint32_t* pipe, uint8_t index)
{
	uint8_t ball = (*pipe<<(index*8))>>24;
	*pipe &= indexes[index];

	return ball;
}

/*
 * Asserts that ball is inserted on index with value Empty = 0
 */
bool insertAtIndex(uint32_t* pipe, uint8_t ball, uint8_t index)
{		
	uint8_t r = ((index*3)+3)%4;
	assert(!ballAtIndex(*pipe, index));
	*pipe |= ((uint32_t) ball)<<(8*r);
	return true;
}

bool move(uint32_t* pipe1, uint32_t* pipe2)
{
	assert(!emptyPipe(*pipe1));
	assert(!filledPipe(*pipe2));
	uint8_t ball = clearAtIndex(pipe1, pipeSpot(*pipe1)-1);
	insertAtIndex(pipe2, ball, pipeSpot(*pipe2));
	return true;
}



uint32_t craftPipe(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	return ( (((((a<<8) | b) << 8 ) | c)<<8) | d);
}

bool boardPrint(struct Board* b)
{
	printf("=========================\n");
	for(uint8_t i = 0; i<4; i++)
	{
		uint8_t r = ((i*3)+3)%4;
		for(uint8_t j = 0; j< b->pipes; j++){
			uint32_t x = (b->state[j]<<(r*8))>>(24);
			printf("[ %2d ]",x);
		}
		printf("\n");
	}
	printf("=========================\n");

	return true;
}

bool pipe_solved(uint32_t pipe)
{
	uint8_t b0 = ballAtIndex(pipe, 0);
	uint8_t b1 = ballAtIndex(pipe, 1);
	uint8_t b2 = ballAtIndex(pipe, 2);
	uint8_t b3 = ballAtIndex(pipe, 3);
	return (b0 == b1 && b1 == b2 && b2 == b3);
}

uint32_t* UInt32_ptr_deep_cpy(uint32_t* state, uint8_t size)
{
	uint32_t* s = malloc(sizeof(uint32_t)*size);
	for(uint8_t i = 0; i < size; i++)
	{
		s[i] = state[i];
	}
	return s;
}

bool move_is_valid(uint32_t giver, uint32_t reciever)
{
	if(filledPipe(reciever)) return false;
	if(emptyPipe(giver)) return false;
	if(emptyPipe(reciever)) return true;
	if(pipe_solved(giver)) return false;
	if(ballAtIndex(giver, pipeSpot(giver)-1) == ballAtIndex(reciever, pipeSpot(reciever)-1)) return true;

	return false;
}

struct Board* SBoard_deep_cpy(struct Board *orig)
{
	struct Board *b = malloc(sizeof(struct Board));
	b->pipes = orig->pipes;
	b->state = UInt32_ptr_deep_cpy(orig->state, b->pipes);
	return b;
}

bool freeSBoard(struct Board *b)
{
	free(b->state);
	free(b);
	return true;
}

bool solved(struct Board* b)
{	
	bool solved = true;
	for(int i = 0; i< b->pipes;i++)
	{
		solved = solved && pipe_solved(b->state[i]);
	}

	return solved;
}

