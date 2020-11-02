#include "cache.h"
#include <stdint.h>
#include <stdio.h>


bool cache_lookup_permutations(struct LList *cache, struct Board *board)
{
	//printf("From cache; AFTER1\n");
	//printf("Board* : %p\n",(void*) board);
	//printf("LList* : %p\n",(void*) cache);
	//printf("Board val: %p\n",(void*) board->state);
	//printf("Cache val: %p\n",(void*) cache->val);
	//printf("Cache next: %p\n",(void*) cache->next);

	bool hit = false;


	while(cache != NULL)
	{
		bool is_perm = true;
		for(int i = 0; i<board->pipes; i++){
			bool match = false;
			for(int j = 0; j<cache->val->pipes; j++)
			{

				//printf("Cache pipes-value: %d\n",cache->val->pipes);
				//printf("From cache; AFTER2\n");
				//uint32_t g = cache->val->state[0];
				//printf("From cache; AFTER2\n");

				uint32_t x = board->state[i];
				uint32_t y = cache->val->state[j];
				if(x==y)
				{
					match = true;
					break;
				}
				//printf("From cache; AFTER3\n");
			}
			is_perm = is_perm && match;
			if(!is_perm) break;
		}

		if(is_perm){
			hit = true;
			break;
		}

		cache = cache->next;
	}

	return hit;
}
