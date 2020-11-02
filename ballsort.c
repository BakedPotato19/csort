#include "solver.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//=====================================================
// Config
// ====================================================

bool pretty_print = false;

//=====================================================
// Section for implementation of the solver algorithm
//
//=====================================================


int main(int argc, char** argv)
{

	uint8_t colors = 3;
	uint8_t pipes = colors + 2;

	struct Board* j = malloc(sizeof(struct Board));

	uint8_t colorsj = 12;
	uint32_t* pipesj = malloc(14*sizeof(uint32_t));
	pipesj[0] = craftPipe(Brown, Lightgreen, Darkblue, Grey);
	pipesj[1] = craftPipe(Darkgreen, Red, Red, Darkgreen);
	pipesj[2] = craftPipe(Pink, Darkblue, Green, Lightblue);
	pipesj[3] = craftPipe(Green, Grey, Brown, Orange);
	pipesj[4] = craftPipe(Darkblue, Orange, Lightblue, Purple);
	pipesj[5] = craftPipe(Yellow, Yellow, Lightgreen, Lightblue);
	pipesj[6] = craftPipe(Green, Darkblue, Purple, Grey);
	pipesj[7] = craftPipe(Pink, Red, Darkgreen, Orange);
	pipesj[8] = craftPipe(Lightblue, Yellow, Grey, Brown);
	pipesj[9] = craftPipe(Purple, Pink, Brown, Green);
	pipesj[10] = craftPipe(Red, Lightgreen, Darkgreen, Pink);
	pipesj[11] = craftPipe(Yellow, Orange, Lightgreen, Pink);
	pipesj[12] = 0;
	pipesj[13] = 0;

	j->pipes = colorsj + 2;
	j->state = pipesj;


	struct Board* b78 = malloc(sizeof(struct Board));
	
	uint8_t colors78 = 7;
	uint32_t *pipes78 = malloc(9*sizeof(uint32_t));
	pipes78[0] = craftPipe(Darkblue, Orange, Grey, Lightblue);
	pipes78[1] = craftPipe(Lightgreen, Darkblue, Grey, Darkblue);
	pipes78[2] = craftPipe(Orange, Lightblue, Pink, Pink);
	pipes78[3] = craftPipe(Lightgreen, Darkblue, Lightgreen, Lightblue);
	pipes78[4] = craftPipe(Red, Pink, Orange, Red);
	pipes78[5] = craftPipe(Lightblue, Lightgreen, Red, Orange);
	pipes78[6] = craftPipe(Grey, Red, Pink, Grey);
	pipes78[7] = 0;
	pipes78[8] = 0; 

	b78->pipes = 9;
	b78->state = pipes78;

	struct Board* b191 = malloc(sizeof(struct Board));
	
	uint8_t colors191 = 7;
	uint32_t *pipes191 = malloc(15*sizeof(uint32_t));
	pipes191[0] = craftPipe(Brown, Pink, Lightgreen, Brown);
	pipes191[1] = craftPipe(Purple, Orange, Darkblue, Lightblue);
	pipes191[2] = craftPipe(Lightgreen, Red, Green, Darkgreen);
	pipes191[3] = craftPipe(Green, Pink, Brown, Yellow);
	pipes191[4] = craftPipe(Orange, Grey, Yellow, Lightblue);
	pipes191[5] = craftPipe(Darkblue, Lightgreen, Darkblue, Green);
	pipes191[6] = craftPipe(Darkgreen, Pink, Orange, Brown);
	pipes191[7] = craftPipe(Lightblue, Grey, Purple, Darkgreen);
	pipes191[8] = craftPipe(Red, Red, Green, Lightblue);
	pipes191[9] = craftPipe(Lightgreen, Pink, Red, Purple);
	pipes191[10] = craftPipe(Darkgreen, Grey, Orange, Purple);
	pipes191[11] = craftPipe(Yellow, Grey, Yellow, Darkblue);
	pipes191[12] = 0; 
	pipes191[13] = 0; 

	b191->pipes = 14;
	b191->state = pipes191;


	struct Board* b73 = malloc(sizeof(struct Board));
	uint8_t colors73 = 9;
	uint32_t *pipes73 = malloc(11*sizeof(struct Board));
	pipes73[0] = craftPipe(Orange, Darkblue, Green, Pink);
	pipes73[1] = craftPipe(Grey, Orange, Purple, Red);
	pipes73[2] = craftPipe(Red, Lightgreen, Grey, Lightgreen);
	pipes73[3] = craftPipe(Darkblue, Darkblue, Lightgreen, Pink);
	pipes73[4] = craftPipe(Orange, Green, Red, Lightblue);
	pipes73[5] = craftPipe(Green, Lightblue, Grey, Lightblue);
	pipes73[6] = craftPipe(Grey, Purple, Red, Purple);
	pipes73[7] = craftPipe(Lightblue, Pink, Darkblue, Lightgreen);
	pipes73[8] = craftPipe(Pink, Green, Orange, Purple);
	pipes73[9] = 0;
	pipes73[10] = 0;


	b73->pipes = 11;
	b73->state = pipes73;

	struct Node *solution = solve(b73);

	if(solution!=NULL)
	{
		printf("##################PRINTING SOLUTION###############\n");
		while(solution!=NULL)
		{
			boardPrint(solution->val);
			solution = solution->parent;
		}
	}

	

	return EXIT_SUCCESS;
	
}
