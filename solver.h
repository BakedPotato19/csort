#include "cache.h"

struct Node{
	struct Board* val;
	struct LList* children;
	struct Node* parent;
	bool fetched;
};

struct Node *solve(struct Board *head);
