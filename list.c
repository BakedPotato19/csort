#include "list.h"

bool freeSList(struct LList *node)
{
	freeSBoard(node->val);
	free(node);
	return true;
}

struct LList* append(struct LList* newHead, struct LList* oldHead)
{
	newHead->next = oldHead;
	return newHead;
}

struct LList* pop(struct LList* oldHead)
{
	struct LList* newHead = oldHead->next;			
	freeSList(oldHead);
	return newHead;
}

struct LList* createNode(struct Board* val)
{
	struct LList* l = malloc(sizeof(struct LList));
	l->val = val;
	l->next = NULL;
	return l;
}


