#include <stdint.h>
#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

//=====================================================
// Config
// ====================================================

bool pretty_print = false;



//=====================================================
// Section for implementation of the game BallSort
//
//=====================================================
/*
 * Define ball colors
 */

enum colors{Empty, Brown, Lightgreen, Darkblue, Grey, Darkgreen, Red, Pink,
			Green, Lightblue, Orange, Purple, Yellow};

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

struct Board
{
	uint32_t* state;
	uint8_t pipes;
};


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
	for(uint8_t i = 0; i<4; i++)
	{
		uint8_t r = ((i*3)+3)%4;
		for(uint8_t j = 0; j< b->pipes; j++){
			uint32_t x = (b->state[j]<<(r*8))>>(24);
			printf("[ %2d ]",x);
		}
		printf("\n");
	}

	return true;
}

//=====================================================
// Section for implementation of the solver algorithm
//
//=====================================================


int main(int argc, char** argv)
{

	uint8_t colors = 3;
	uint8_t pipes = colors + 2;

	struct Board b;
	struct Board *ptr = &b;

	uint32_t* pipeptr = malloc(pipes * sizeof(uint32_t));
	pipeptr[0] = craftPipe(Darkblue,Orange,Red,Darkblue);
	pipeptr[1] = craftPipe(Orange, Orange, Red, Darkblue);
	pipeptr[2] = craftPipe(Red, Darkblue, Orange, Red);
	pipeptr[3] = 0;
	pipeptr[4] = 0;

	b.state = pipeptr;
	
	b.pipes = pipes;

	boardPrint(ptr);
	move(&pipeptr[0], &pipeptr[3]);
	move(&pipeptr[0], &pipeptr[3]);
	move(&pipeptr[0], &pipeptr[3]);
	move(&pipeptr[0], &pipeptr[3]);
	printf("-----------------------\n");
	boardPrint(ptr);

	return EXIT_SUCCESS;
	
}
