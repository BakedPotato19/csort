#include "solver.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

bool freeNode(struct Node* n)
{
	freeSList(n->children);
	freeSBoard(n->val);
	free(n);
	return true;
}

struct Node* next_node(struct Node* current)
{
	if(current->children != NULL)
	{
		struct Node* n = malloc(sizeof(struct Node));
		n->children = NULL;
		n->fetched = false;
		n->parent = current;
		n->val = SBoard_deep_cpy(current->children->val);
		current->children = pop(current->children);
		return n;
	}
	else{
		free(current);
		return current->parent;

	}
}

struct Node* solve(struct Board *starting_state)
{
	// Initialize parent Node
	struct Node *current = malloc(sizeof(struct Node));
	current->parent = NULL;
	current->children = NULL;
	current->val = starting_state;
	current->fetched = false;


	// Initialize cache
	struct LList* cache = malloc(sizeof(struct LList));
	cache->val = SBoard_deep_cpy(current->val);
	cache->next = NULL;

	uint64_t i = 0;

	while(true)
	{
		i++;
		// Check for solve
		if(current == NULL)
		{
			printf("NO SOLUTION!");
			return NULL;
		}

		if(solved(current->val))
		{
			boardPrint(current->val);
			printf("SOLVED!!");
			return current;		
		}

		printf("\n%d",(int)i);
		boardPrint(current->val);

		// Fetch
		// - Meaning initilizing children
		if(!current->fetched)
		{
			for(uint8_t i = 0; i<current->val->pipes; i++)
			{
				for(uint8_t j = 0; j< current->val->pipes; j++)
				{
					if(i!=j && move_is_valid(current->val->state[i],current->val->state[j]))
					{
						struct Board *copy = SBoard_deep_cpy(current->val);
						move(&(copy->state[i]), &(copy->state[j]));
						struct Board *cac_cpy = SBoard_deep_cpy(copy);
						if(!cache_lookup_permutations(cache, copy))
						{
							current->children = append(createNode(copy),current->children);
							cache = append(createNode(cac_cpy),cache);
						}
						else{
							freeSBoard(copy);
						}
					}
					
				}
			}
			current->fetched = true;
		}
		current = next_node(current);	

	}
	return NULL;
}
